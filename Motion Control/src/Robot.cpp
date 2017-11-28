#include <iostream>
#include <memory>
#include <string>

#include <Joystick.h>
#include <SampleRobot.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <RobotDrive.h>
#include <Timer.h>
#include <Talon.h>
#include <Encoder.h>
#include <PIDController.h>

using namespace std;

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
	frc::RobotDrive myRobot {0,1,2,3}; // robot drive system
	frc::Joystick stick { 0 }; // only joystick
	frc::SendableChooser<std::string> chooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	Encoder *leftEnc = new Encoder(0, 1, false, Encoder::EncodingType::k4X);
	Encoder *rightEnc = new Encoder(2, 3, true, Encoder::EncodingType::k4X);
	const int wheelDiameter = 8;
	const int encoderRes = 2048;
	const float PI = 3.1415927;
	Talon *frontLeft = new Talon(0);
	Talon *backLeft = new Talon(1);
	Talon *frontRight = new Talon(2);
	Talon *backRight = new Talon(3);

public:
	Robot() {
		//Note SmartDashboard is not initialized here, wait until RobotInit to make SmartDashboard calls
		myRobot.SetExpiration(0.1);
	}

	void RobotInit() {
		chooser.AddDefault(autoNameDefault, autoNameDefault);
		chooser.AddObject(autoNameCustom, autoNameCustom);
		frc::SmartDashboard::PutData("Auto Modes", &chooser);
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
		std::string autoSelected = frc::SmartDashboard::GetString("Auto Selector", autoNameDefault);
		std::cout << "Auto selected: " << autoSelected << std::endl;
		bool CaptureComplete = false;
		bool CaptureAuto = false;
		bool Capturing = frc::SmartDashboard::GetBoolean("Capturing", false);
		string AutoValues;
		leftEnc->SetDistancePerPulse((wheelDiameter*PI)/encoderRes);
		rightEnc->SetDistancePerPulse((wheelDiameter*PI)/encoderRes);
		AutoValues.resize(11);
		int Line;
		if(Capturing)
		{
			AutoValues = to_string(leftEnc->GetDistance())  + "," + to_string(rightEnc->GetDistance()) + "\n";
			cout << AutoValues;
			frc::SmartDashboard::PutString("Auto Values", AutoValues);
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
