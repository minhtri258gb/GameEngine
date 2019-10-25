
#include "../../Main.h"
#include "Command.h"


// List command
void cmd_void();
void cmd_exit();
void cmd_forward();
void cmd_back();
void cmd_moveleft();
void cmd_moveright();
void cmd_jump();
void cmd_sprint();
void cmd_use();
void cmd_debugfrustumculling();
void cmd_debugnoclip();
void cmd_debugorigin();
void cmd_test1();
void cmd_test2();


Command::Command()
{
	m_listCMD.resize(354);
	for(int i=0; i<354; i++)
		m_listCMD[i] = &cmd_void;
}

Command::~Command()
{
}

void Command::update()
{
	for(short idkey = 0; idkey < 354; idkey++)
		if(m_keyAction.test(idkey))
		{
			if(!m_keyLoop.test(idkey))
				m_keyAction.set(idkey, false);
			(*m_listCMD.at(idkey))();
		}
}

void Command::keyPress(int idkey, bool state)
{
	if(state)
		m_keyAction.set(idkey, true);
	else if(m_keyLoop.test(idkey))
		m_keyAction.set(idkey, false);
}

void Command::keyBind(string key, string command)
{
	int idkey = convertKey(key);
	if(idkey == -1)
	{
		cout << "[Command:keybind] warning: key \"" << key << "\" false to bind" << endl;
		return;
	}

	m_keyLoop.set(idkey, command[0] == '+' ? true : false);
	m_listCMD[idkey] = convertFunction(command);
}

int Command::convertKey(string key)
{
	int length = key.length();
	if(!length)
		return -1;

	int firstchar = key[0];
	if(64 < firstchar && firstchar < 91)
	{
		if(length == 1)
		{
			return firstchar;										// A - Z
		}
		else
		{
			switch (firstchar) {
			case 'B':
				if(key[1] == 'A')
					return 259;						// BACKSPACE
				break;
			case 'C':
				if(key[1] == 'A')
					return 280;						// CAPS_LOCK
				break;
			case 'D':
				if(key[1] == 'E')
					return 261;						// DELETE
				else if(key[1] == 'O')
					return 264;					// DOWN
				break;
			case 'E':
				if(key[1] == 'S')
					return 256;						// ESCAPE
				else if(key[1] == 'N')
				{
					if(key[2] == 'T')
						return 257;					// ENTER
					else if(key[2] == 'D')
						return 269;				// END
				}
				break;
			case 'F':
				if(key[1] == '1')
				{
					if(length == 2)
						return 290;						// F1
					else
						return 251 + key[2];						// F10 - F11
				}
				else if(key[1] == '2')
				{
					if(length == 2)
						return 291;						// F1
					else
					{											// F20 - F25
						if(261 + key[2] < 315)
							return 261 + key[2];
						else
							return -1;
					}
				}
				else if(key[1] != '0')
					return 241 + key[1];		// F3 - F9
				break;
			case 'H':
				if(key[1] == 'O')
					return 268;						// HOME
				break;
			case 'I':
				if(key[1] == 'N')
					return 260;						// INSERT
				break;
			case 'K':
				if(key[3] < 65)
					return 272 + key[3];				// KP_0 - KP_9
				else if(key[3] == 'D')
				{
					if(key[4] == 'E')
						return 330;					// KP_DECIMAL
					else if(key[4] == 'I')
						return 331;				// KP_DIVIDE
				}
				else if(key[3] == 'M')
					return 332;					// KP_MULTIPLY
				else if(key[3] == 'S')
					return 333;					// KP_SUBTRACT
				else if(key[3] == 'A')
					return 334;					// KP_ADD
				else if(key[3] == 'E')
				{
					if(key[4] == 'N')
						return 335;					// KP_ENTER
					else if(key[4] == 'Q')
						return 336;				// KP_EQUAL
				}
				break;
			case 'L':
				if(length > 4)
				{
					if(key[5] == 'S')
					{
						if(key[6] == 'H')
							return 340;				// LEFT_SHIFT
						else if(key[6] == 'U')
							return 343;			// LEFT_SUPER
					}
					else if(key[5] == 'C')
						return 341;			// LEFT_CONTROL
					else if(key[5] == 'A')
						return 342;				// LEFT_ALT
				}
				else
					return 263;									// LEFT
				break;
			case 'M':
				if(key[1] == 'O')
				{
					if(key[5] == '1')
						return 351;					// MOUSE1
					else if(key[5] == '2')
						return 352;				// MOUSE2
					else if(key[5] == '3')
						return 353;				// MOUSE3
				}
				else if(key[1] == 'W')
				{
					if(key[6] == 'D')
						return 349;					// MWHEELDOWN
					else if(key[6] == 'U')
						return 350;				// MWHEELUP
				}
				else
					return 348;									// MENU
				break;
			case 'N':
				return 282;									// NUM_LOCK
			case 'P':
				if(key[2] == 'I')
					return 283;						// PRINT_SCREEN
				else if(key[2] == 'U')
					return 284;					// PAUSE
				else if(key[2] == 'G')
				{
					if(key[5] == 'U')
						return 266;					// PAGE_UP
					else if(key[5] == 'D')
						return 267;				// PAGE_DOWN
				}
				break;
			case 'R':
				if(length > 5)
				{
					if(key[5] == 'S')
					{
						if(key[6] == 'H')
							return 344;				// RIGHT_SHIFT
						else if(key[6] == 'U')
							return 347;			// RIGHT_SUPER
					}
					else if(key[5] == 'C')
						return 345;			// RIGHT_CONTROL
					else if(key[5] == 'A')
						return 346;				// RIGHT_ALT
				}
				else
					return 262;									// RIGHT
				break;
			case 'S':
				if(key[1] == 'P')
					return 32;						// SPACE
				else if(key[1] == 'C')
					return 281;					// SCROLL_LOCK
				break;
			case 'T':
				if(key[1] == 'A')
					return 258;						// TAB
				break;
			case 'U':
				if(key[1] == 'P')
					return 265;						// UP
				break;
			}
		}
	}
	else if(47 < firstchar && firstchar < 58)
	{
		return firstchar;											// 0 - 9
	}
	else
	{
		switch (firstchar) {
		case '\'':
			return 39;
		case ',':
			return 44;
		case '-':
			return 45;
		case '.':
			return 46;
		case '/':
			return 47;
		case ';':
			return 59;
		case '=':
			return 61;
		case '[':
			return 91;
		case '\\':
			return 92;
		case ']':
			return 93;
		case '`':
			return 96;
		}
	}

	return -1;
}

pFuncCMD Command::convertFunction(string command)
{
	switch(command[0])
	{
	case '+':
		switch(command[1])
		{
		case 'a':
			if(command == "+attack")				return cmd_void;
			else if(command == "+attack2")			return cmd_void;
			break;
		case 'b':
			if(command == "+back")					return cmd_back;
			break;
		case 'f':
			if(command == "+forward")				return cmd_forward;
			break;
		case 'm':
			if(command == "+moveleft")				return cmd_moveleft;
			else if(command == "+moveright")		return cmd_moveright;
			else if(command == "+moveup")			return cmd_void;
			else if(command == "+movedown")			return cmd_void;
			break;
		case 's':
			if(command == "+showscores")			return cmd_void;
			else if(command == "+sprint")			return cmd_sprint;
			break;
		case 'u':
			if(command == "+use")					return cmd_use;
			break;
		}
		break;
	case 'c':
		if(command == "cancelselect")				return cmd_void;
		else if(command == "chat")					return cmd_void;
		else if(command == "commandmenu")			return cmd_void;
		else if(command == "crouch")				return cmd_void;
		break;
	case 'd':
		if(command == "drop")						return cmd_void;
		else if(command == "debugfrustumcull")		return cmd_debugfrustumculling;
		else if(command == "debugnoclip")			return cmd_debugnoclip;
		else if(command == "debugorigin")			return cmd_debugorigin;
		break;
	case 'e':
		if(command == "exit")						return cmd_exit;
	case 'i':
		if(command == "invnext")					return cmd_void;
		else if(command == "invprev")				return cmd_void;
		break;
	case 'j':
		if(command == "jump")						return cmd_jump;
		break;
	case 'r':
		if(command == "reload")						return cmd_void;
		break;
	case 's':
		if(command == "slot10")						return cmd_void;
		else if(command == "slot1")					return cmd_void;
		else if(command == "slot2")					return cmd_void;
		else if(command == "slot3")					return cmd_void;
		else if(command == "slot4")					return cmd_void;
		else if(command == "slot5")					return cmd_void;
		else if(command == "slot6")					return cmd_void;
		else if(command == "slot7")					return cmd_void;
		else if(command == "slot8")					return cmd_void;
		else if(command == "slot9")					return cmd_void;
		break;
	case 't':
		if(command == "toggleconsole")				return cmd_void;
		else if(command == "test1")					return cmd_test1;
		else if(command == "test2")					return cmd_test2;
		break;
	}
	return cmd_void;
}

void cmd_void()
{

}
