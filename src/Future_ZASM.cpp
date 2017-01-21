COOLSCROLL = (get_bit(quest_rules,qr_COOLSCROLL)!=0 ? 1 : 0) |
                 (get_bit(quest_rules,qr_OVALWIPE)!=0 ? 2 : 0) |
                 (get_bit(quest_rules,qr_TRIANGLEWIPE)!=0 ? 4 : 0) |
                 (get_bit(quest_rules,qr_SMASWIPE)!=0 ? 8 : 0);
		 
//Set Continue DMap

		 game->set_continue_dmap(zinit.start_dmap);
		 

	