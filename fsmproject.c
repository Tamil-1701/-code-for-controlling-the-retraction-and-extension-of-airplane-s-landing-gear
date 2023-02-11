#include <stdio.h>
void Initiate_State_Machine();
void GearDown();
void CheckingBeforeTakeOFF();
void RaisingGear();
void GearUp();
void CheckBeforeLanding();
void LoweringGear();
static void(*statetable[])(void)={GearDown, CheckingBeforeTakeOFF, RaisingGear, GearUp, CheckBeforeLanding, LoweringGear};
typedef enum State
{
GEAR_DOWN,
CHECKING_BEFORE_TAKEOFF,
RAISING_GEAR,
GEAR_UP,
CHECK_BEFORE_LANDING,
LOWERING_GEAR,
}State_Type;
typedef enum Switch
{
on,
off//plane is on groung
}Switch_status;
typedef enum pilot_lever
{
Raising,
falling
}pilot_lever;
typedef enum hydraulic_mechanism
{
working,
not_working
}hydraulic_mechanism;

static volatile Switch_status squat_switch;
static volatile Switch_status limit_switch;
static volatile pilot_lever pl;
static volatile hydraulic_mechanism hm;

State_Type current_state;

typedef struct
{
char* current_state_indication;
char* light;
char* direction_valve_status;
char* landing_gear_hydraulic_control;
char* Gas_Pressurized_Spring_system_status[2];

}State_Table;

static State_Table State_Machine[6]={{"GearDown","Green","Down","Enabled",{NULL,NULL}},
{"CheckingBeforeTakeOFF","Green","Down","Enabled",{NULL,NULL}},
{"RaisingGear","Red","Up","Enabled",{NULL,NULL}},
{"GearUp","Off","NULL","Disbled",{NULL,NULL}},
{"CheckBeforeLanding","Red","Down","Enabled",{NULL,NULL}},
{"LoweringGear","Green","Down","Enabled",{"Disabled","Enabled"}}
};
int main()
{
Initiate_State_Machine();
while(1)
{
statetable[current_state]();
}
}
void GearDown(void)
{
current_state=GEAR_DOWN;
printf("Enter the status of pilot's lever and squat switch");
fflush(stdout);
scanf("%d %d",&pl,&squat_switch);
if(pl==Raising && squat_switch==on)
{
current_state=CHECKING_BEFORE_TAKEOFF;
printf("current state:%s\n",State_Machine[current_state].current_state_indication);
printf("Light is :%s\n", State_Machine[current_state].light);
}
else
{
GearDown();
}
}

//CheckingBeforeTakeOFF
void CheckingBeforeTakeOFF(void)
{
current_state=CHECKING_BEFORE_TAKEOFF;
printf("Enter the status of pilot's lever and squat switch and hydraulic mechanism:");
fflush(stdout);
scanf("%d %d",&pl,&squat_switch,&hm);
if(pl==falling&&squat_switch==off)
{
GearDown();
}
else if(pl==Raising && squat_switch==on && hm==working)
{
current_state=RAISING_GEAR;
printf("Current State:%s\n",State_Machine[current_state].current_state_indication);
printf("Light is:%s\n",State_Machine[current_state].light);
printf("Status of Direction valve:%s\n",State_Machine[current_state].direction_valve_status);
}
else if(pl==Raising && squat_switch==on && hm==not_working)
{
current_state=RAISING_GEAR;
printf("Current State:%s\n",State_Machine[current_state].current_state_indication);
printf("Light is:%s\n",State_Machine[current_state].light);
printf("Status of Direction valve:%s\n",State_Machine[current_state].direction_valve_status);
printf("Status of gas pressurised Spring System:%s\n",State_Machine[current_state].Gas_Pressurized_Spring_system_status);
}
}
//RaisingGear
void RaisingGear(void)
{
current_state=RAISING_GEAR;
printf("Enter the status of pilot's lever and limit switch:");
fflush(stdout);
scanf("%d %d",&pl,&limit_switch);
if(pl==falling && limit_switch==on)
{
current_state=CHECK_BEFORE_LANDING;
printf("Current State:%s\n",State_Machine[current_state].current_state_indication);
printf("Light is:%s\n",State_Machine[current_state].light);
printf("Landing Gear Hydraulic Control:%s\n",State_Machine[current_state].landing_gear_hydraulic_control);
}
else if(pl==Raising && limit_switch==off)
{
current_state=GEAR_UP;
printf("Current State:%s\n",State_Machine[current_state].current_state_indication);
printf("Light is:%s\n",State_Machine[current_state].light);
printf("Landing Gear Hydraulic Control:%s\n",State_Machine[current_state].landing_gear_hydraulic_control);
}
else
{
RaisingGear();
}
}
//GearUp
void GearUp(void)
{
current_state=GEAR_UP;
printf("Enter the status of pilot's lever:");
fflush(stdout);
scanf("%d",&pl);
if(pl==falling)
{
current_state=CHECK_BEFORE_LANDING;
printf("Current State:%s\n",State_Machine[current_state].current_state_indication);
printf("Light is:%s\n",State_Machine[current_state].light);
printf("Landing Gear Hydraulic Control:%s\n",State_Machine[current_state].landing_gear_hydraulic_control);
}
else
{
GearUp();
}

}
//CheckBeforeLanding
void CheckBeforeLanding(void)
{
current_state=CHECK_BEFORE_LANDING;
printf("Enter the status of pilot's lever and hydraulic mechanism status:");
fflush(stdout);
scanf("%d %d",&pl,&hm);
if(pl==falling && hm==working)
{
current_state=LOWERING_GEAR;
printf("Current State:%s\n",State_Machine[current_state].current_state_indication);
printf("Light is:%s\n",State_Machine[current_state].light);
printf("Status of Direction valve:%s\n",State_Machine[current_state].direction_valve_status);
}
else if(pl==falling && hm==not_working)
{
current_state=LOWERING_GEAR;
printf("Current State:%s\n",State_Machine[current_state].current_state_indication);
printf("Light is:%s\n",State_Machine[current_state].light);
printf("Status of Direction valve:%s\n",State_Machine[current_state].direction_valve_status);
printf("Status of gas pressurised Spring System:%s\n",State_Machine[current_state].Gas_Pressurized_Spring_system_status);
}
else if(pl==(Raising))
{
CheckBeforeLanding();
}
}
//LoweringGear.
void LoweringGear(void)
{
current_state=LOWERING_GEAR;
printf("Enter the status of pilot's lever and limit switch:");
fflush(stdout);
scanf("%d %d",&pl,&limit_switch);
if(pl==falling && limit_switch==on)
{
current_state=CHECKING_BEFORE_TAKEOFF;
printf("Current State:%s\n",State_Machine[current_state].current_state_indication);
printf("Light is:%s\n",State_Machine[current_state].light);
}
else if(pl==Raising && limit_switch==off)
{
current_state=GEAR_DOWN;
printf("Current State:%s\n",State_Machine[current_state].current_state_indication);
printf("Light is:%s\n",State_Machine[current_state].light);
printf("Landing Gear Hydraulic Control:%s\n",State_Machine[current_state].landing_gear_hydraulic_control);
}
if(limit_switch==off)
{
LoweringGear();
}
}
//Initiate_State_Machine
void Initiate_State_Machine()
{
current_state==GEAR_DOWN;
printf("The Finite State Machine is Intialized and current the program is in""GearDown State & Light is:%s\n",State_Machine[current_state].light);
}
