#pragma once
#include "../tier0/Vector.h"
#include "../tier1/checksum_crc.h"

struct CameraThirdData_t
{
	float   m_flPitch;
	float   m_flYaw;
	float   m_flDist;
	float   m_flLag;
	Vector  m_vecHullMin;
	Vector  m_vecHullMax;
};

// Created with ReClass.NET 1.2 by KN4CK3R
class CInput
{
public:
	typedef struct
	{
		unsigned int AxisFlags;
		unsigned int AxisMap;
		unsigned int ControlMap;
	} joy_axis_t;
	enum
	{
		GAME_AXIS_NONE = 0,
		GAME_AXIS_FORWARD,
		GAME_AXIS_PITCH,
		GAME_AXIS_SIDE,
		GAME_AXIS_YAW,
		MAX_GAME_AXES
	};
	enum
	{
		MOUSE_ACCEL_THRESHHOLD1 = 0,	// if mouse moves > this many mickey's double it
		MOUSE_ACCEL_THRESHHOLD2,		// if mouse moves > this many mickey's double it a second time
		MOUSE_SPEED_FACTOR,				// 0 = disabled, 1 = threshold 1 enabled, 2 = threshold 2 enabled

		NUM_MOUSE_PARAMS,
	};
	// Has the mouse been initialized?
	bool		m_fMouseInitialized;
	// Is the mosue active?
	bool		m_fMouseActive;
	// Has the joystick advanced initialization been run?
	bool		m_fJoystickAdvancedInit;
	// Used to support hotplugging by reinitializing the advanced joystick system when we toggle between some/none joysticks.
	bool		m_fHadJoysticks;

	// Accumulated mouse deltas
	float		m_flAccumulatedMouseXMovement;
	float		m_flAccumulatedMouseYMovement;
	float		m_flPreviousMouseXPosition;
	float		m_flPreviousMouseYPosition;
	float		m_flRemainingJoystickSampleTime;
	float		m_flKeyboardSampleTime;

	// Flag to restore systemparameters when exiting
	bool		m_fRestoreSPI;
	// Original mouse parameters
	int			m_rgOrigMouseParms[NUM_MOUSE_PARAMS];
	// Current mouse parameters.
	int			m_rgNewMouseParms[NUM_MOUSE_PARAMS];
	bool		m_rgCheckMouseParam[NUM_MOUSE_PARAMS];
	// Are the parameters valid
	bool		m_fMouseParmsValid;
	// Joystick Axis data
	joy_axis_t m_rgAxes[6];
	// List of queryable keys
	void* m_pKeys;

	// Is the 3rd person camera using the mouse?
	bool		m_fCameraInterceptingMouse;
	// Are we in 3rd person view?
	bool		m_fCameraInThirdPerson;
	// Should we move view along with mouse?
	bool		m_fCameraMovingWithMouse;


	// Is the camera in distance moving mode?
	bool		m_fCameraDistanceMove;
	// Old and current mouse position readings.
	int			m_nCameraOldX;
	int			m_nCameraOldY;
	int			m_nCameraX;
	int			m_nCameraY;

	// orthographic camera settings
	bool		m_CameraIsOrthographic;

	QAngle		m_angPreviousViewAngles;

	float		m_flLastForwardMove;

	float m_flPreviousJoystickForward;
	float m_flPreviousJoystickSide;
	float m_flPreviousJoystickPitch;
	float m_flPreviousJoystickYaw;

	class CVerifiedUserCmd
	{
	public:
		CUserCmd	m_cmd;
		CRC32_t		m_crc;
	};

	CUserCmd* m_pCommands;
	CVerifiedUserCmd* m_pVerifiedCommands;

	CameraThirdData_t* m_pCameraThirdData;

	/*void* N0000004F; //0x0000
	char pad_0008[136]; //0x0008
	void* m_pKeys; //0x0090
	bool m_fCameraInterceptingMouse; //0x0098
	bool m_fCameraInThirdPerson; //0x0099
	bool m_fCameraMovingWithMouse; //0x009A
	char pad_009B[21]; //0x009B
	QAngle m_angPreviousViewAngles; //0x00B0
	float m_flLastForwardMove; //0x00BC
	uint32_t m_nClearInputState; //0x00C0
	char pad_00C4[892]; //0x00C4*/

	virtual		void		Init_All(void);
	virtual		void		Shutdown_All(void);
	virtual		int			GetButtonBits(int);
	virtual		void		CreateMove(int sequence_number, float input_sample_frametime, bool active);
	virtual		void		ExtraMouseSample(float frametime, bool active);
	virtual		bool		WriteUsercmdDeltaToBuffer(bf_write* buf, int from, int to, bool isnewcommand);
	virtual		void		EncodeUserCmdToBuffer(bf_write& buf, int slot);
	virtual		void		DecodeUserCmdFromBuffer(bf_read& buf, int slot);

	virtual		CUserCmd* GetUserCmd(int sequence_number);

	virtual		void		MakeWeaponSelection(C_BaseCombatWeapon* weapon);

	virtual		float		KeyState(ButtonCode_t* key);
	virtual		int			KeyEvent(int down, ButtonCode_t keynum, const char* pszCurrentBinding);
	virtual		ButtonCode_t* FindKey(const char* name);

	virtual		void		ControllerCommands(void);
	virtual		void		Joystick_Advanced(void);
	virtual		void		Joystick_SetSampleTime(float frametime);
	virtual		void		IN_SetSampleTime(float frametime);

	virtual		void		AccumulateMouse(void);
	virtual		void		ActivateMouse(void);
	virtual		void		DeactivateMouse(void);

	virtual		void		ClearStates(void);
	virtual		float		GetLookSpring(void);

	virtual		void		GetFullscreenMousePos(int* mx, int* my, int* unclampedx = NULL, int* unclampedy = NULL);
	virtual		void		SetFullscreenMousePos(int mx, int my);
	virtual		void		ResetMouse(void);

	//	virtual		bool		IsNoClipping( void );
	virtual		float		GetLastForwardMove(void);
	virtual		float		Joystick_GetForward(void);
	virtual		float		Joystick_GetSide(void);
	virtual		float		Joystick_GetPitch(void);
	virtual		float		Joystick_GetYaw(void);
	virtual		void		ClearInputButton(int bits);

	virtual		void		CAM_Think(void);
	virtual		int			CAM_IsThirdPerson(void);
	virtual		void		CAM_ToThirdPerson(void);
	virtual		void		CAM_ToFirstPerson(void);
	virtual		void		CAM_StartMouseMove(void);
	virtual		void		CAM_EndMouseMove(void);
	virtual		void		CAM_StartDistance(void);
	virtual		void		CAM_EndDistance(void);
	virtual		int			CAM_InterceptingMouse(void);

	// orthographic camera info
	virtual		void		CAM_ToOrthographic();
	virtual		bool		CAM_IsOrthographic() const;
	virtual		void		CAM_OrthographicSize(float& w, float& h) const;

	virtual		float		CAM_CapYaw(float fVal) { return fVal; }

}; //Size: 0x0448