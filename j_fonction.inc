/****************************************/
/*										*/
/*			Include : j_fonction 0.1	*/
/*			Creer par : Jaber 			*/
/*										*/
/****************************************/


#include <a_samp>

/*

	native GiveHealth(playerid,Float:Health)
	native ClearChatForAll() 
	native GetPlayerFPS(playerid)
	native GetName(playerid)
	native GetPlayerSpeed(playerid)
	native TakeHealth(playerid, Float:Health)
	native Slap(playerid)
	native GetVehicleSpeed(vehicleid)
	native DisarmAll()
	native GetAmmo(playerid)
	native JailPlayer(playerid)
	native UnJailPlayer(playerid)
	native GiveAllCash(cash)
	native GiveAllScore(score)
	native vehicle_lock(vehicleid)
	native vehicle_unlock(vehicleid)
	native banEx(playerid, raison[])
	native SlapEx(playerid, raison[])
	native KickEx(playerid, raison[])
	native FreezePlayerEx(playerid , temps = 5000) // le temp par default est 5 seconde , si le temp est a -1 le joueur sera freeze indefiniment
	native ToggleFps(playerid, toggle) // toggle peut etre 0 ou 1 | 1 = Oui | 0 = Non

*/
/***** Variable ****/
// System de First view
new FirstPerson[MAX_PLAYERS]; 
new FirstPersonObject[MAX_PLAYERS]; 
new bool:FPS[MAX_PLAYERS]; 

/***** Forward *****/
forward OnPlayerUnfreeze(playerid);

/**** Fonctions ****/
stock GiveHealth(playerid,Float:Health)
{
	new Float:health; GetPlayerHealth(playerid,health);
	return SetPlayerHealth(playerid,health+Health);
}

stock ClearChatForAll() 
{
    for(new i;i<100;i++) 
	{
    SendClientMessageToAll(0xFFFFFFAA," "); 
	}
	return 1;
}

/*stock GetPlayerFPS(playerid)
{
	SetPVarInt(playerid, "DrunkL", GetPlayerDrunkLevel(playerid));
 	if(GetPVarInt(playerid, "DrunkL") < 100) SetPlayerDrunkLevel(playerid, 2000);
 		else{
   			if(GetPVarInt(playerid, "LDrunkL") != GetPVarInt(playerid, "DrunkL"))
      		{
       			SetPVarInt(playerid, "FPS", (GetPVarInt(playerid, "LDrunkL") - GetPVarInt(playerid, "DrunkL")));
          		SetPVarInt(playerid, "LDrunkL", GetPVarInt(playerid, "DrunkL"));
            	if((GetPVarInt(playerid, "FPS") > 0) && (GetPVarInt(playerid, "FPS") < 256))
             	{
              		return GetPVarInt(playerid, "FPS") - 1;
                }
			}
		}
  	return 0;
}*/

stock GetPlayerFPS(playerid)
{
	new pDrunkLevelLast[MAX_PLAYERS];
	new pFPS[MAX_PLAYERS];
	new drunknew;
	
	drunknew = GetPlayerDrunkLevel(playerid);
	pDrunkLevelLast[playerid]= 0;
	pFPS[playerid]= 0;
	
	if (drunknew < 100)
	{ 
		SetPlayerDrunkLevel(playerid, 2000);
	} 
	else 
	{	
		if (pDrunkLevelLast[playerid] != drunknew) {
			
			new wfps = pDrunkLevelLast[playerid] - drunknew;
			
			if ((wfps > 0) && (wfps < 200))
				pFPS[playerid] = wfps;
			
			pDrunkLevelLast[playerid] = drunknew;
		}
		
	}
	return pFPS;
}

stock GetName(playerid)
{
		new name[MAX_PLAYER_NAME];
		GetPlayerName(playerid, name, sizeof(name) );
		return name;
}

stock GetPlayerSpeed(playerid)
{
        if(playerid != INVALID_PLAYER_ID)
        {
                new Float:Pos[3],Float:PS;
                GetPlayerVelocity(playerid, Pos[0], Pos[1], Pos[2]);
                PS = floatsqroot(Pos[0]*Pos[0] + Pos[1]*Pos[1] + Pos[2]*Pos[2])*200;
                return floatround(PS,floatround_round);
        }
        return INVALID_PLAYER_ID;
}

stock TakeHealth(playerid, Float:Health)
{
		new Float:hp;
		GetPlayerHealth(playerid, hp);
		new calc = floatsub(hp, Health);
		SetPlayerHealth(playerid, calc);
		return 1;
}

stock Slap(playerid)
{
		new Float:Pos[3];
		GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2] );
		SetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]+10);
		return 1;
}
stock SlapEx(playerid, raison[])
{
		new tmp[128];
		format(tmp, 128, "[Serveur] %s a etait Slap pour [ %s ]", GetName(playerid), raison);
		SendClientMessageToAll(0xFF0000AA, tmp);
		new Float:Pos[3];
		GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2] );
		SetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]+10);
		return 1;
}
stock GetVehicleSpeed(vehicleid)
{
        if(vehicleid != INVALID_VEHICLE_ID)
        {
                new Float:Pos[3],Float:VS ;
                GetVehicleVelocity(vehicleid, Pos[0], Pos[1], Pos[2]);
                VS = floatsqroot(Pos[0]*Pos[0] + Pos[1]*Pos[1] + Pos[2]*Pos[2])*200;
                return floatround(VS,floatround_round);
        }
        return INVALID_VEHICLE_ID;
}

stock DisarmAll()
{
		for(new i; i < MAX_PLAYERS; i++) ResetPlayerWeapons(i);
		return 1;
}

stock GetAmmo(playerid)
{
		new weapon[3];
		weapon[0] = GetWeaponSlot(GetPlayerWeapon(playerid) );
		GetPlayerWeaponData(playerid, weapon[0], weapon[1], weapon[2]);
		return weapon[2];
}

stock JailPlayer(playerid)
{
        SetPlayerInterior(playerid,6);
		SetPlayerPos(playerid, 265.6881,76.6573,1001.0391);
		TogglePlayerControllable(playerid,0);
        SetPlayerCameraPos(playerid,269.5,77.5,1002);
		return SetPlayerCameraLookAt(playerid,264.6288,77.5742,1001.0391);
}
 
stock UnJailPlayer(playerid)
{
		SetPlayerPos(playerid, 267.6288,77.5742,1001.0391);
		TogglePlayerControllable(playerid,1);
		return SetCameraBehindPlayer(playerid);
}

stock GiveAllCash(cash)
{
	for(new i; i < MAX_PLAYERS; i++) GivePlayerMoney(i, cash);
	return 1;
}

stock GiveAllScore(score)
{
	for(new i; i < MAX_PLAYERS; i++) GivePlayerMoney(i, score);
	return 1;
}

stock vehicle_unlock(vehicleid)
{
	for(new i; i < MAX_PLAYERS; i++)
	{
		SetVehicleParamsForPlayer(vehicleid, i, 0, 0);
	}
	return 1;
}

stock vehicle_lock(vehicleid)
{
	for(new i; i < MAX_PLAYERS; i++)
	{
		SetVehicleParamsForPlayer(vehicleid, i, 0, 1);
	}
	return 1;
}

stock banEx(playerid, raison[])
{
	if(!IsPlayerConnected(playerid)) return 0;
	
	new tmp[128];
	format(tmp, 128, "[Serveur] {FFFFFF}%s a etait ban du serveur (Raison: %s)", GetName(playerid), raison);
	SendClientMessageToAll(0xFF0000AA, tmp);
	
	return Ban(playerid);
}

stock KickEx(playerid, raison[])
{
	if(!IsPlayerConnected(playerid)){ SendClientMessage(playerid, 0xFF0000AA,"Le Joueur specifier n'existe pas"); return 0;}

	new tmp[128];
	format(tmp, 128, "[Serveur]{FFFFFF} %s a etait Kick du serveur (Raison: %s)", GetName(playerid), raison);
	SendClientMessageToAll(0xFF0000AA, tmp);	
	return Kick(playerid);
}

stock FreezePlayerEx(playerid, temps = 5000)
{
		if(temps == -1)
		{
		TogglePlayerControllable(playerid, false);
		SendClientMessage(playerid, 0xFF0000AA,"[Admin]{FFFFFF}Vous avez étais Freeze jusqu'a nouvelle ordre" );
		}
		else if(temps != -1)
		{
		new tmp[128];
		format(tmp, 128,"[Admin]{FFFFFF}Vous avez étais Freeze pour %s seconde", temps);
		SendClientMessage(playerid, 0xFF0000AA, tmp);
        TogglePlayerControllable(playerid, false);
        SetTimerEx("OnPlayerUnfreeze", temps, false, "i", playerid);
		}
        return 1;
}
 
stock ToggleFps(playerid, toggle)  
{ 
	switch(toggle){
	case 1:
	{
    FirstPersonObject[playerid] = CreateObject(19300, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0); 
    AttachObjectToPlayer(FirstPersonObject[playerid],playerid, 0.0, 0.12, 0.7, 0.0, 0.0, 0.0);
    AttachCameraToObject(playerid, FirstPersonObject[playerid]);
    FirstPerson[playerid] = 1; 
    CallLocalFunction("OnPlayerHaveFirstPerson", "i", playerid);} 
	case 0:
	{
    SetCameraBehindPlayer(playerid);
    DestroyObject(FirstPersonObject[playerid]);
    FirstPerson[playerid] = 0;
    CallLocalFunction("OnPlayerDoNotHaveFirstPerson", "i", playerid);}
	} 
    return 1; 
} 
 
/**** CallBack ****/

public OnPlayerUnfreeze(playerid)
{
	TogglePlayerControllable(playerid, true);
	return 1;
}
