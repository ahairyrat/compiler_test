
typedef enum{
	COMMENT_NO_ERROR		=	0x00,
	COMMENT_MULTILINE		=	0x10,
	COMMENT_SINGLELINE_ONLY	=	0x20,
	COMMENT_UNKNOWN_ERROR	=	0x40
} commentError;

#include <string>

commentError removeComment(std::string input, std::string &output, commentError currentState);

void debugTest();
