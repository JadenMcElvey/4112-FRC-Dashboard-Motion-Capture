#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>

#include <Joystick.h>
#include <Talon.h>
#include <SampleRobot.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <RobotDrive.h>
#include <Timer.h>
#include <Talon.h>
#include <Encoder.h>
#include <PIDController.h>
#include <NetworkTables/NetworkTable.h>


/**
 * This is a demo program showing the use of the RobotDrive class.
 * The SampleRobot class is the base of a robot application that will
 * automatically call your Autonomous and OperatorControl methods at the right
 * time as controlled by the switches on the driver station or the field
 * controls.
 *
 * WARNING: While it may look like a good choice to use for your code if you're
 * inexperienced, don't. Unless you know what you are doing, complex code will
 * be much more difficult under this system. Use IterativeRobot or Command-Based
 * instead if you're new.
 */
class Robot: public frc::SampleRobot {
	frc::RobotDrive myRobot {4,5,6,7}; // robot drive system
	frc::Joystick stick { 0 }; // only joystick
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	Encoder *leftEnc = new Encoder(5, 4, false, Encoder::EncodingType::k4X);
	Encoder *rightEnc = new Encoder(7, 6, true, Encoder::EncodingType::k4X);
	Talon fleftDrive {0};
	Talon frightDrive {1};
	Talon bleftDrive {2};
	Talon brightDrive {3};
	double p = 0.1;
	double i = 0.001;
	double d = 0.0;
	const int wheelDiameter = 8;
	const int encoderRes = 2048;
	const float PI = 3.1415927;


public:
	Robot() {

		//Note SmartDashboard is not initialized here, wait until RobotInit to make SmartDashboard calls
		myRobot.SetExpiration(0.1);
	}

	void RobotInit() {

	}

	/*
	 * This autonomous (along with the chooser code above) shows how to select
	 * between different autonomous modes using the dashboard. The sendable
	 * chooser code works with the Java SmartDashboard. If you prefer the
	 * LabVIEW Dashboard, remove all of the chooser code and uncomment the
	 * GetString line to get the auto name from the text box below the Gyro.
	 *
	 * You can add additional auto modes by adding additional comparisons to the
	 * if-else structure below with additional strings. If using the
	 * SendableChooser make sure to add them to the chooser code above as well.
	 */
	void Autonomous() {
		// auto autoSelected = chooser.GetSelected();
		myRobot.SetSafetyEnabled(false);
		fleftDrive.SetSafetyEnabled(false);
		frightDrive.SetSafetyEnabled(false);
		bleftDrive.SetSafetyEnabled(false);
		brightDrive.SetSafetyEnabled(false);
		frc::SmartDashboard::PutBoolean("WriteCapture", false);
		frc::SmartDashboard::PutBoolean("Capturing", false);
		frc::SmartDashboard::PutNumber("Line", 0);
		frc::SmartDashboard::PutString("ReadValue", "");
		std::string autoSelected = frc::SmartDashboard::GetString("Auto Selector", autoNameDefault);
		std::cout << "Auto selected: " << autoSelected << std::endl;
		leftEnc->SetDistancePerPulse((wheelDiameter*PI)/encoderRes);
		rightEnc->SetDistancePerPulse((wheelDiameter*PI)/encoderRes);
		frc::Wait(1);
		bool capturing = frc::SmartDashboard::GetBoolean("Capturing", true);
		if(autoSelected == "Capturing")
		{
			std::cout << "capture" << std::endl;
			/*
			std::string WriteValues;
			for(int i = 0; i < 300; ++i)
			{
				WriteValues += std::to_string(leftEnc->GetDistance())  + "," + std::to_string(rightEnc->GetDistance()) + "\n";
				frc::Wait(0.05);
			}
			std::cout << WriteValues << std::endl;
			frc::SmartDashboard::PutString("AutoValues", WriteValues);
			frc::SmartDashboard::PutBoolean("WriteCapture", true);
			*/
		}
		else if (autoSelected == "Read")
		{
			std::cout << "read" << std::endl;

			/*
			PIDController PIDfleft(p, i, d, leftEnc, &fleftDrive);
			PIDController PIDbleft(p, i, d, leftEnc, &bleftDrive);
			PIDController PIDfright(p, i, d, rightEnc, &frightDrive);
			PIDController PIDbright(p, i, d, rightEnc, &brightDrive);
			PIDfleft.SetOutputRange(-1, 1);
			PIDbleft.SetOutputRange(-1, 1);
			PIDfright.SetOutputRange(-1, 1);
			PIDbright.SetOutputRange(-1, 1);

			leftEnc->Reset();
			rightEnc->Reset();
			std::cout << std::to_string(leftEnc->GetDistance())  + "," + std::to_string(rightEnc->GetDistance()) << std::endl;
			PIDfleft.SetSetpoint(0);
			PIDbleft.SetSetpoint(0);
			PIDfright.SetSetpoint(0);
			PIDbright.SetSetpoint(0);

			PIDfleft.Enable();
			PIDbleft.Enable();
			PIDfright.Enable();
			PIDbright.Enable();

			for(int line = 0; line < 300; ++line)
			{
				std::string readValue = frc::SmartDashboard::GetString("ReadValue", "");

				std::cout << readValue << std::endl;
				std::string delimiter = ",";
				std::string leftDistance;
				leftDistance.resize(8);
				std::string rightDistance;
				rightDistance.resize(8);
				std::string::iterator delimitIter;

				delimitIter = std::search(readValue.begin(), readValue.end(), delimiter.begin(), delimiter.end());
				std::copy(readValue.begin(), delimitIter, leftDistance.begin());
				std::copy(delimitIter, readValue.end(), rightDistance.begin());

				PIDfleft.SetSetpoint(stod(leftDistance));
				PIDbleft.SetSetpoint(stod(leftDistance));
				PIDfright.SetSetpoint(stod(rightDistance));
				PIDbright.SetSetpoint(stod(rightDistance));

				while(!(PIDfleft.OnTarget() && PIDbleft.OnTarget()) && !(PIDfright.OnTarget() && PIDbright.OnTarget()))
				{
				std::cout << std::to_string(leftEnc->GetDistance())  + "," + std::to_string(rightEnc->GetDistance()) << std::endl;
				}
			}
			*/




		 }




	}

	/*
	 * Runs the motors with arcade steering.
	 */
	void OperatorControl() override {
		myRobot.SetSafetyEnabled(true);
		while (IsOperatorControl() && IsEnabled()) {
			// drive with arcade style (use right stick)
			myRobot.ArcadeDrive(stick);

			// wait for a motor update time
			frc::Wait(0.005);
		}
	}

	/*
	 * Runs during test mode
	 */
	void Test() override {

	}
};

START_ROBOT_CLASS(Robot)
