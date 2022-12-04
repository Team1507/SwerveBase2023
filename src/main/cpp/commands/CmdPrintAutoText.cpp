#include "commands/CmdPrintAutoText.h"
#include <iostream>


CmdPrintAutoText::CmdPrintAutoText(std::string text) 
{
  m_text = text;
}

void CmdPrintAutoText::Initialize() 
{  
 std::cout << m_text << std::endl; 
}
