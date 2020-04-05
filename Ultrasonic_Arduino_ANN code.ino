//Ultrasonic distance measurement system  using ANN to compensate distance measurement
//Also calculates total execution time of each iteration in loop() section
#define numberSensorInputs 4 //Four inputs 
#define numberHiddenNeurons 10// Hidden layer  neurons
unsigned long start, finished, elapsed;
float sensorValue[numberSensorInputs]= {33.25,59.36,352.33,3.98};// (temp,humid,speed, Us_distance)
float hiddenLayerOut[numberHiddenNeurons];

float hiddenLayerWeights[numberHiddenNeurons][numberSensorInputs]={{1.6371,-0.7703,-0.6584,-1.1078},{1.0160,0.0420,-1.0106,-0.9221},{-0.5624,-0.0172,0.5470,-0.4746},{0.4322,-1.2402,0.55981,1.2310},{1.7009,-1.6292,-0.6434,0.6908},{0.0449,-1.2651,-0.0341,-1.1867},{-0.7326,1.1126,-1.0892,1.8240}, {1.2758,-0.3411,1.9356,0.9899},{-1.7398,1.3679,-0.4049,1.0618},{-0.8274,1.4160,0.2483,2.0885  }};
//Hiddenlayer weights 
float hiddenLayerBias[numberHiddenNeurons]= {-1.6879,-1.0072,0.4312,-0.4594,-0.4865,-0.1598,-0.8945,1.2600,-1.7837,-2.2628}; //Bias Hidden Layer

float outputLayerWeights[numberHiddenNeurons]= {0.0119,-0.5786,-1.9667,-0.0058,0.0059,-0.0085,0.0039,-0.0015,-0.0023,0.0109}; //Output layer bias
float outputLayerBias = 0.3760;

void setup() {

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

void loop() {
  Serial.println("Start...");
  unsigned long start = micros(); // measured in microseconds 
  // Parameter passed is the neuron number.
    for(int j=0; j<numberHiddenNeurons; j++){
      hiddenLayerOut[j] = ComputeHiddenTransferFunc(SumOfHiddenNeurons(j));//calling hidden layer transfer function,tan-sigmoid function
    }

  float sum = SumOfOutputNeuron();
  Serial.println(sum,6);// 6 decimal places
  unsigned long finished = micros();
  Serial.println("Finished");
  elapsed=finished-start; // total execution time after each iteration
  Serial.print(elapsed);
  Serial.println(" microseconds  elapsed");
  Serial.println();
    
   delay(2000); //delay 
}

float SumOfOutputNeuron(){
  float result = 0;

    for(int j=0; j<numberHiddenNeurons; j++){
      result = result+outputLayerWeights[j]*hiddenLayerOut[j];
     // Serial.print("Output Neuron Product for ");
     // Serial.print(j);
     // Serial.print(" is ");
     // Serial.println(result,6);// 6 decimal places
    }

  result = result+outputLayerBias; // linear output layer transfer function
  //Serial.print("Output Neuron Sum with bias: ");
  //Serial.println(result,6);// 6 decimal places
  return result;
}

float SumOfHiddenNeurons(int neuronNumber){
  float result = 0;

    for(int j=0; j<numberSensorInputs; j++){
      //Serial.print("Hidden Neuron Weight for ");
      //Serial.print(j);Serial.print(" is ");
     // Serial.println(hiddenLayerWeights[neuronNumber][j],6); // 6 decimal places
      result = result+hiddenLayerWeights[neuronNumber][j]*sensorValue[j];
     //Serial.print("Hidden Neuron Product for ");
     // Serial.print(j);
     // Serial.print(" is ");
      //Serial.println(result,6);// 6 decimal places
    }

  result = result+hiddenLayerBias[neuronNumber];
 // Serial.print("Hidden Neuron Sum with bias: ");
  //Serial.println(result,6);// 6 decimal places
  return result;
}

/* Computing Tan-Sigmoid Transfer Function for hidden layer*/
float ComputeHiddenTransferFunc(float neuronSum){
  float result = 0;
  result = (2.0/(1.0 + exp(-neuronSum)))-1;
//  Serial.print("Hidden Neuron output: ");
 // Serial.println(result,6);// 6 decimal places
  return result;
}
