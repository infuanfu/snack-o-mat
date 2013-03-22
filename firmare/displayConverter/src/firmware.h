

/** 
 * converts a byte from the format used by the MICREL 10957p 
 * to ASCII used by the new VF-Display.
 */
inline char convert(char in) {
	
	if (in >= 0x01 && in <= 0x1A) {
		return 'A' + in - 0x01;
	} else if (in >= 0x30 && in <= 0x39) {
		return '0' + in - 0x30;
	}

	switch (in) {
		case 0x00: return '@';
		case 0x1B: return '[';
		case 0x1C: return '/';
		case 0x1D: return ']';
		case 0x1E: return '^';
		case 0x1F: return '_';
		case 0x20: return ' ';
		case 0x21: return '!';
		case 0x22: return '"';
		case 0x23: return '#';
		case 0x24: return '$';
		case 0x25: return '%';
		case 0x26: return '&';
		case 0x27: return '´';
		case 0x28: return '(';
		case 0x29: return ')';
		case 0x2A: return '*';
		case 0x2B: return '+';
		case 0x2C: return '\'';
		case 0x2D: return '_';
		case 0x2E: return '.';
		case 0x2F: return '\\';
		
		case 0x3A: return ':';
		case 0x3B: return ';';
		case 0x3C: return '<';
		case 0x3D: return '=';
		case 0x3E: return '>';
		case 0x3F: return '?';
		
		case 0x6C: return '.';
		case 0x6E: return ',';

		default: return ' ';
	}

}

