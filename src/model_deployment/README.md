# Edge Impulse Model for Pathfinder V1

This directory contains information about the TinyML model used in Pathfinder V1 for object recognition.

## Model Overview

The Pathfinder V1 uses an image classification model trained with Edge Impulse to recognize common obstacles and objects that visually impaired individuals might encounter. The model is optimized for the XIAO ESP32S3's limited resources.

## Training Dataset

The model was trained on a custom dataset that included:
- Common indoor obstacles (chairs, tables, stairs, doors)
- Outdoor navigation elements (sidewalks, crosswalks, stairs)
- Safety hazards (poles, construction signs, wet floor signs)

## Model Architecture

- Model Type: Convolutional Neural Network (CNN)
- Input: 96x96 pixel grayscale images
- Layers: 
  - Conv2D layers with depthwise separable convolutions
  - Max pooling layers
  - Dense layers with dropout for classification
- Output: Classification probabilities for recognized objects

## Deployment Process

1. Train the model in Edge Impulse
2. Optimize the model for the ESP32S3
3. Export the model as an Arduino library
4. Integrate the library with the main Arduino code

## Example Integration Code

```cpp
#include <EdgeImpulse-Arduino-SDK.h>
#include "ei-pathfinder-project-arduino-1.0.0/model-parameters/model_metadata.h"

// Function to run inference on captured image
void runObjectDetection(uint8_t *image_data) {
  ei_impulse_result_t result;
  
  // Create signal from image data
  signal_t signal;
  signal.total_length = EI_CLASSIFIER_INPUT_WIDTH * EI_CLASSIFIER_INPUT_HEIGHT;
  signal.get_data = &get_signal_data;
  
  // Run inference
  EI_IMPULSE_ERROR res = run_classifier(&signal, &result, false);
  
  if (res == EI_IMPULSE_OK) {
    // Process results
    for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
      ei_printf("  %s: %.2f\n", result.classification[ix].label, 
                                result.classification[ix].value);
    }
    
    // Get prediction with highest confidence
    size_t pred_index = 0;
    float pred_value = 0;
    
    for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
      if (result.classification[ix].value > pred_value) {
        pred_value = result.classification[ix].value;
        pred_index = ix;
      }
    }
    
    // Use the prediction if confidence is high enough
    if (pred_value > 0.7) {
      const char* object_name = result.classification[pred_index].label;
      // Provide feedback based on detected object
      provideFeedback(object_name);
    }
  }
}
```

## Recreating the Model

To recreate the model:

1. Create an Edge Impulse account at [edgeimpulse.com](https://www.edgeimpulse.com/)
2. Create a new project
3. Upload training images or collect data using your ESP32S3 camera
4. Create an impulse with the following blocks:
   - Image data preprocessing (96x96 pixels, grayscale)
   - Image feature extraction (transfer learning with MobileNetV2)
   - Classification (Neural Network Classifier)
5. Train the model
6. Test the model performance
7. Deploy as Arduino library
8. Import the library to your Arduino project

## Model Performance

- Accuracy: ~85% on test dataset
- Latency: ~300ms per inference on ESP32S3
- Memory Usage: ~200KB of flash memory
