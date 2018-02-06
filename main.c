#include <stdio.h>
# ifdef __APPLE__
#  include "OpenCL/opencl.h"
# else
#  include "CL/cl.h"
# endif
#include <time.h>

void CL_CALLBACK onOpenCLError(const char *errinfo,  const void *private_info,
							   size_t cb, void *user_data)
{
	(void)private_info;
	(void)cb;
	(void)user_data;
	printf("Error while creating context or working in this context : %s\n", errinfo);
}

int					main(void) {
	clock_t start = clock();
	cl_int	res;
	size_t	i;
//The code as a string
	char *program_text;

	program_text =	"\n" \
			"__kernel void square(                    \n" \
			"   __global double* input,               \n" \
			"   __global double* output,              \n" \
			"   int count)                            \n" \
			"{  int i = get_global_id(0);             \n" \
			"   size_t z;                             \n" \
			"   double      buf;                      \n" \
			"                                         \n" \
			"     (void)count;                        \n" \
			"       z = 0;                            \n" \
			"           buf = __cl_pow(input[i], 20);      \n" \
			"              while (z < 1)      \n" \
			"             {                           \n" \
			"               buf = sqrt(buf);          \n" \
			"                       z++;              \n" \
			"                   }                     \n" \
			"                output[i] = buf;         \n" \
			"             }                           \n";

/***************************************************************************************/
/*****                    Getting available platforms                              *****/
/***************************************************************************************/
	cl_uint numEntries;
	cl_platform_id *platforms;
	cl_uint numPlatforms;
	char		platform_name[128];

	numEntries = 1;
	platforms = (cl_platform_id*)malloc(sizeof(cl_platform_id)*numEntries);
	res = clGetPlatformIDs(numEntries, platforms, &numPlatforms);
	if(res != CL_SUCCESS)
	{
		printf("Error while getting available platforms.\n");
		exit(1);
	}
	clGetPlatformInfo(platforms[0], CL_PLATFORM_NAME, 128, platform_name, NULL);
/****************************************************************************************/
/*****                     Getting available GPU devices                            *****/
/****************************************************************************************/
	cl_uint             maxDevices;
	cl_device_id*       deviceIDs;
	cl_uint             numDevices;
	char				name[128];
	maxDevices = 1;
	deviceIDs = (cl_device_id*)malloc(maxDevices*sizeof(cl_device_id));
	res = clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_GPU, maxDevices,
							deviceIDs, &numDevices);
	if(res != CL_SUCCESS)
	{
		res = clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_CPU, maxDevices,
							 deviceIDs, &numDevices);
		if(res != CL_SUCCESS)
		{
			printf("Error while getting available devices.\n");
			exit(1);
		}
	}
	clGetDeviceInfo(deviceIDs[0], CL_DEVICE_NAME, 128, name, NULL);
/****************************************************************************************/
/*****                     Creation of the OpenCL context                           *****/
/****************************************************************************************/
	cl_context_properties*  properties;
	cl_uint                 usedDevices;
	cl_context				context;

	properties = 0;
	usedDevices = 1;
	context = clCreateContext(properties, usedDevices, deviceIDs, &onOpenCLError, NULL, &res);
	if(res != CL_SUCCESS)
	{
		printf("Error while creating of the OpenCL context.\n");
		exit(1);
	}

/****************************************************************************************/
/*****                     Creation of the command queue                            *****/
/****************************************************************************************/
	cl_command_queue_properties commandQueueProperties;
	cl_command_queue commands;

	commandQueueProperties = 0;
	commands = clCreateCommandQueue(context, deviceIDs[0], commandQueueProperties, &res);
	if(res != CL_SUCCESS)
	{
		printf("Error while creating of the command queue.\n");
		exit(1);
	}
/****************************************************************************************/
/*****                  Creation of the program from sources                        *****/
/****************************************************************************************/
	cl_uint     stringsCountForSource;
	size_t*     stringLengths;

	stringsCountForSource = 1;
	stringLengths = NULL;
	cl_program program =
			clCreateProgramWithSource(context, 1, (const char**)&program_text, stringLengths, &res);
	if(res != CL_SUCCESS)
	{
		printf("Error while creation of the program from sources.\n");
		exit(1);
	}
/****************************************************************************************/
/*****                       Compilation of the program                             *****/
/****************************************************************************************/
	char*               compileOptions = "-I ../";
	const cl_device_id* deviceList;
	cl_uint             devicesCount;

	deviceList = NULL;
	devicesCount = 0;
	res = clBuildProgram(program, devicesCount, deviceList, compileOptions, NULL, NULL);
	if(res != CL_SUCCESS)
	{
		printf("Error while compilation of the program.\n");
		exit(1);
	}
/****************************************************************************************/
/*****                          Creation of the kernel                              *****/
/****************************************************************************************/
	cl_kernel kernel = clCreateKernel(program, "square", &res);
	if(res != CL_SUCCESS)
	{
		printf("Error while creating of the kernel.\n");
		exit(1);
	}
/****************************************************************************************/
/*****                      Initialization of input data                            *****/
/****************************************************************************************/
	//Initialization
	size_t numberOfValues;
	size_t sizeOfBuffers;
	double* inputDoubles;
	cl_mem inputBuffer;

	numberOfValues = 256;
	sizeOfBuffers = numberOfValues*sizeof(double);
	inputDoubles = (double*)malloc(sizeOfBuffers);
	i = 0;
	while (i < numberOfValues)
	{
		inputDoubles[i] = i + 0.1;
		i++;
	}
	//Creation and allocation of the input data for the kernel
	inputBuffer = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeOfBuffers, NULL, &res);
	if(res != CL_SUCCESS)
	{
		printf("Error while initializing of input data.\n");
		exit(1);
	}
	//Declarations for the copy of data
	cl_bool     blockingWrite;
	size_t      offset;
	cl_event    dataInputCopyEvent;
	cl_event*   eventsToWait;
	cl_uint     numEvents;

	blockingWrite = CL_TRUE;
	offset = 0;
	eventsToWait = NULL;
	numEvents = 0;
	res = clEnqueueWriteBuffer(commands, inputBuffer, blockingWrite, offset, sizeOfBuffers, inputDoubles, numEvents, eventsToWait, &dataInputCopyEvent);
	if(res != CL_SUCCESS)
	{
		printf("Error while writing input data.\n");
		exit(1);
	}
	cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeOfBuffers, NULL, &res);
	if(res != CL_SUCCESS)
	{
		printf("Error while initializing output data.\n");
		exit(1);
	}

/****************************************************************************************/
/*****                         Setting kernel arguments                             *****/
/****************************************************************************************/
	res = 0;
	res |= clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer);
	res |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
	res |= clSetKernelArg(kernel, 2, sizeof(size_t), &numberOfValues);
	if(res != CL_SUCCESS)
	{
		printf("Error while setting kernel arguments.\n");
		exit(1);
	}
/****************************************************************************************/
/*****                   Execution of the kernel !!!!                           *********/
/****************************************************************************************/
	cl_uint   workDim;
	size_t*   globalWorkOffset;
	size_t    globalWorkSize;
	size_t    localWorkSize;
	cl_event  kernelExecEvent;

	eventsToWait = NULL;
	numEvents = 0;
	workDim = 1;
	globalWorkOffset = NULL;
	globalWorkSize =  numberOfValues;
	res = clGetKernelWorkGroupInfo(kernel, deviceIDs[0],
								   CL_KERNEL_WORK_GROUP_SIZE,
									  sizeof(localWorkSize), &localWorkSize, NULL);
	if(localWorkSize > numberOfValues)
		localWorkSize = numberOfValues;
	if(res != CL_SUCCESS)
	{
		printf("Error while getting maximum work group size.\n");
		exit(1);
	}
	res = clEnqueueNDRangeKernel(commands, kernel, workDim, globalWorkOffset, &globalWorkSize, &localWorkSize, numEvents, eventsToWait, &kernelExecEvent);
	if(res != CL_SUCCESS)
	{
		printf("Error while executing the kernel.\n");
		exit(1);
	}
/****************************************************************************************/
/*****                          Getting back the results                            *****/
/****************************************************************************************/
//Declarations
	cl_bool     blockingRead;
	double*     resultArray;
	cl_event    readResultsEvent;

	eventsToWait = NULL;
	numEvents = 0;
	offset = 0;
	blockingRead = CL_TRUE;
//Allocations
	resultArray = (double*)malloc(numberOfValues*sizeof(double));
	clFinish(commands);
//Execution
	clEnqueueReadBuffer(commands, outputBuffer, blockingRead, offset, sizeOfBuffers, resultArray, numEvents, eventsToWait, &readResultsEvent);

	i = 0;
	while(i < numberOfValues)
	{
		printf("%f\n", resultArray[i]);
		if ((i + 1) % 10 == 0 && i != 0)
		{
			printf("\n");
		}
		i++;
	}
	clock_t stop = clock();
	double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
	printf("\nTime elapsed: %.5f\n", elapsed);
	printf("The number of device can be used: %d\n", numDevices);
	printf("We are using:\t\t%s\n", platform_name);
	printf("We are using:\t\t%s\n", name);
	printf("The local work size is: %zu\n", localWorkSize);
	printf("The global work size is: %zu\n", globalWorkSize);
	return (0);
}