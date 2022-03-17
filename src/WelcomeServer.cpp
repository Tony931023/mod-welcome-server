#include "ScriptMgr.h"
#include "Chat.h"
#include "Player.h"
#include "Config.h"
#include "TicketMgr.h"
#include "GameTime.h"



class WelcomeServer : public PlayerScript {

public:
    WelcomeServer() : PlayerScript("WelcomeServer") {}

    bool _isEnableCC	    = sConfigMgr->GetBoolDefault("WelcomeServer.Enable", true);
    bool _isAnnounceCC	    = sConfigMgr->GetBoolDefault("WelcomeServer.Announce", true);

	// Announce Module
	void OnLogin(Player *player) 
	{
		if (_isEnableCC)
		{
			if (_isAnnounceCC)
			{
				ChatHandler(player->GetSession()).SendSysMessage("This server is running the |cff4CFF00Welcome Server |rmodule.");
			}
		}

        std::string pname = player->GetName();
        std::string uptime = secsToTimeString(GameTime::GetUptime().count()).c_str();
        std::string player_ip = player->GetSession()->GetRemoteAddress();
        uint32 playeronline = sWorld->GetPlayerCount();

        if(player->GetSession()->GetSecurity() == SEC_PLAYER){

        ChatHandler(player->GetSession()).PSendSysMessage("|cffff0000=================================|r");
        ChatHandler(player->GetSession()).PSendSysMessage("|cff00ff00Bienvenido,|r %s", pname.c_str()),"Recuerda votar por el server cada 12 horas en www.amanthul.nat.cu";
        ChatHandler(player->GetSession()).PSendSysMessage("|cff00ff00Tu direcci""\xC3\xB3""n IP es:|r %s", player_ip.c_str());
        ChatHandler(player->GetSession()).PSendSysMessage("|cff00ff00En este momento hay|r %u |cff00ff00jugadores en l""\xC3\xAD""nea|r", playeronline);        
        ChatHandler(player->GetSession()).PSendSysMessage("|cff00ff00Servidor Online durante:|r %s", uptime.c_str());
        ChatHandler(player->GetSession()).PSendSysMessage("|cffff0000=================================|r");
        //ChatHandler(player->GetSession()).SendSysMessage("Welcome back online! Your character has been saved to the database, buffed and healed! Now remember to vote every 12 hours on www.unforgivenwow.com!");

        player->GetSession()->SendNotification("BIENVENIDO A Aman'thul");
        player->GetSession()->SendNotification("! %s !", player->GetName());
        player->CastSpell(player, 11543, 1);
        }

        if (player->GetSession()->GetSecurity() >= SEC_MODERATOR)
        {
            
            uint16 gmlvl = player->GetSession()->GetSecurity();
            std::string gmname = player->GetName();
            uint16 tickets = sTicketMgr->GetOpenTicketCount();
            
            ChatHandler(player->GetSession()).PSendSysMessage("|cffff0000=================================|r");
            ChatHandler(player->GetSession()).PSendSysMessage("|cff00ff00Bienvenido,|r %s", gmname.c_str());
            ChatHandler(player->GetSession()).PSendSysMessage("|cff00ff00Tu nivel de cuenta es:|r %u", gmlvl);
            ChatHandler(player->GetSession()).PSendSysMessage("|cff00ff00Tu direcci""\xC3\xB3""n IP es:|r %s", player_ip.c_str());
            ChatHandler(player->GetSession()).PSendSysMessage("|cff00ff00En este momento hay|r %u |cff00ff00jugadores en l""\xC3\xAD""nea|r", playeronline);
            ChatHandler(player->GetSession()).PSendSysMessage("|cff00ff00Tickets abiertos:|r %u", tickets);
            ChatHandler(player->GetSession()).PSendSysMessage("|cff00ff00Servidor Online durante:|r %s", uptime.c_str());
            ChatHandler(player->GetSession()).PSendSysMessage("|cffff0000=================================|r");
            return;
        }

	}

};


void AddWelcomeServerScripts()
{ 
    new WelcomeServer();
}
