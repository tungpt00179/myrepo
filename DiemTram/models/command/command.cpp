#include "command.h"

QString Command::toString()
{
    return m_command + " " + m_data  + "\r\n";
}
