// COPYRIGHT: Open source by GPL (GNU General Public License)
// Based on C5.0 GPL Edition provided by Rulequest Research Pty Ltd.
//===================================================================
//
// Platform dependet functions
//
//===================================================================
//  FEB 2013  Creation:                       Ramirez, GOD RECEPRION
//===================================================================

#ifndef CrossPlatform_H
#define CrossPlatform_H

double GetSystemClock();

void SetRunTimeStackSize(int iValue_KB);

void C5DeleteFile(const char* iFileName);


#endif //CrossPlatform_H
