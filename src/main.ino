/*
 * Pathfinder V1 - Navigation Assistant for Visually Impaired
 * 
 * Created by Team VYSE at TinkerHub TinyML Hackathon 2024
 * Team Members:
 * - Muzammil Latheef Seedi
 * - Jeevan Joseph
 * - Mizhab A S
 * - Muhammed Irfan Nazar
 * 
 * Repository created: 2025-04-22
 */

#include <NewPing.h>

// Uncomment if you have access to Edge Impulse library
// #include <EdgeImpulse-Arduino-SDK.h>
// #include "ei-pathfinder-project-arduino-1.0.0/src/edge-impulse-sdk/classifier/ei_run_classifier.h"

//========== PIN DEFINITIONS ==========
#define TRIGGER_PIN   2    // Ultrasonic sensor trigger pin
#define ECHO_PIN      3    // Ultrasonic sensor echo pin
#define MOTOR_PIN     5    // Vibration motor control pin
#define BUZZER_PIN    6    // Buzzer control pin

//========== CONSTANTS ==========
#define MAX_DISTANCE      200   // Maximum distance in cm
#define OBSTACLE_DISTANCE  50   // Distance (in cm) to consider as an obstacle
#define DANGER_DISTANCE    20   // Distance (in cm) for immediate alert
#define DETECTION_INTERVAL 50   // Time between distance measurements (ms)
#define FEEDBACK_INTERVAL 100   // Time between feedback updates (ms)

//========== GLOBAL VARIABLES ==========
unsigned long lastDetectionTime = 0;    // Timestamp of last distance detection
unsigned long lastFeedbackTime = 0;     // Timestamp of last feedback update
unsigned int currentDistance = 0;       // Current measured distance
bool isObstacleDetected = false;        // Flag for obstacle detection status
bool isDangerDetected = false;          // Flag for immediate danger detection

// Initialize ultrasonic sensor
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

//========== SETUP FUNCTION ==========
void setup() {
  // Initialize serial communication for debugging
  Serial.begin(115200);
  
  // Wait for serial to connect, but timeout after 5 seconds
  unsigned long startTime = millis();
  while (!Serial && (millis() - startTime < 5000));
  
  Serial.println("=================================");
  Serial.println("  Pathfinder V1 - Initializing  ");
  Serial.println("=================================");
  
  // Initialize output pins
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Initialize with feedback to indicate startup
  quickStartupSequence();
  
  // Initialize Edge Impulse (if available)
  // if (ei_init() == false) {
  //   Serial.println("Failed to initialize Edge Impulse");
  // } else {
  //   Serial.println("Edge Impulse initialized successfully");
  // }
  
  Serial.println("Pathfinder V1 - Ready to assist!");
  Serial.println("=================================");
}

//========== MAIN LOOP ==========
void loop() {
  // Measure distance at regular intervals
  if (millis() - lastDetectionTime >= DETECTION_INTERVAL) {
    lastDetectionTime = millis();
    measureDistance();
  }
  
  // Update feedback at regular intervals
  if (millis() - lastFeedbackTime >= FEEDBACK_INTERVAL) {
    lastFeedbackTime = millis();
    updateFeedback();
    
    // Optional: Run object detection
    // if available and if an obstacle is detected
    // if (isObstacleDetected) {
    //   runObjectDetection();
    // }
  }
}

//========== HELPER FUNCTIONS ==========

// Function to measure distance using ultrasonic sensor
void measureDistance() {
  // Get distance in centimeters
  currentDistance = sonar.ping_cm();
  
  // Check if reading is valid (0 means out of range)
  if (currentDistance > 0) {
    // Update detection flags based on distance
    isDangerDetected = (currentDistance <= DANGER_DISTANCE);
    isObstacleDetected = (currentDistance <= OBSTACLE_DISTANCE);
    
    // Print distance for debugging
    Serial.print("Distance: ");
    Serial.print(currentDistance);
    Serial.println(" cm");
  } else {
    // No valid reading, assume clear path
    isDangerDetected = false;
    isObstacleDetected = false;
    
    Serial.println("No obstacle detected (out of range)");
  }
}

// Function to update all feedback mechanisms
void updateFeedback() {
  if (isDangerDetected) {
    // Immediate danger - strong alert
    Serial.println("DANGER: Immediate obstacle!");
    activateBuzzer(true);
    activateVibration(true);
  } 
  else if (isObstacleDetected) {
    // Obstacle detected - moderate alert
    Serial.println("WARNING: Obstacle detected");
    activateBuzzer(false);
    activateVibration(true);
  } 
  else {
    // Clear path
    activateBuzzer(false);
    activateVibration(false);
  }
}

// Function to control buzzer
void activateBuzzer(bool isUrgent) {
  if (isUrgent) {
    // Urgent alert - high-pitched tone
    tone(BUZZER_PIN, 2000, 100);
  } else {
    // Turn off buzzer
    noTone(BUZZER_PIN);
  }
}

// Function to control vibration motor
void activateVibration(bool isActive) {
  digitalWrite(MOTOR_PIN, isActive ? HIGH : LOW);
}

// Quick startup sequence to indicate device is turning on
void quickStartupSequence() {
  // Two short buzzes and vibrations to indicate startup
  for (int i = 0; i < 2; i++) {
    tone(BUZZER_PIN, 1500, 100);
    digitalWrite(MOTOR_PIN, HIGH);
    delay(100);
    noTone(BUZZER_PIN);
    digitalWrite(MOTOR_PIN, LOW);
    delay(100);
  }
}

/* 
// Placeholder for object detection using Edge Impulse
void runObjectDetection() {
  Serial.println("Running object detection...");

  // Placeholder for image capture code
  // signal_t signal;
  // camera_capture(&signal);

  // Run the classifier
  // ei_impulse_result_t result;
  // EI_IMPULSE_ERROR err = run_classifier(&signal, &result, false);
  
  // Process and use the results
  // if (err == EI_IMPULSE_OK) {
  //   // Find prediction with highest confidence
  //   float maxConfidence = 0;
  //   size_t maxIndex = 0;
  //   
  //   for (size_t i = 0; i < EI_CLASSIFIER_LABEL_COUNT; i++) {
  //     if (result.classification[i].value > maxConfidence) {
  //       maxConfidence = result.classification[i].value;
  //       maxIndex = i;
  //     }
  //   }
  //   
  //   // If confidence is high enough, provide feedback
  //   if (maxConfidence > 0.7) {
  //     const char* objectName = result.classification[maxIndex].label;
  //     Serial.print("Detected: ");
  //     Serial.print(objectName);
  //     Serial.print(" (");
  //     Serial.print(maxConfidence * 100);
  //     Serial.println("%)");
  //     
  //     // Provide specific feedback based on detected object
  //     provideFeedbackForObject(objectName);
  //   }
  // }
}

// Provide specific feedback based on detected object
void provideFeedbackForObject(const char* objectName) {
  // Different feedback patterns could be implemented here
  // based on the type of object detected
  
  // Example:
  // if (strcmp(objectName, "stairs") == 0) {
  //   // Special pattern for stairs - alternating vibration
  //   alternatingVibrationPattern();
  // } 
  // else if (strcmp(objectName, "door") == 0) {
  //   // Special pattern for doors - double buzz
  //   doubleBuzzPattern();
  // }
}
*/
