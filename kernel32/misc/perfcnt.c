/* $Id: perfcnt.c 37763 2008-11-30 11:42:05Z sginsberg $ */
/*
 * COPYRIGHT:       See COPYING in the top level directory
 * PROJECT:         ReactOS system libraries
 * FILE:            lib/kernel32/misc/perfcnt.c
 * PURPOSE:         Performance counter
 * PROGRAMMER:      Eric Kohl
 */

/* INCLUDES *****************************************************************/

#include <k32.h>

//#define NDEBUG
#include <debug.h>


/* FUNCTIONS ****************************************************************/

/*
 * @implemented
 */
BOOL WINAPI
QueryPerformanceCounter(LARGE_INTEGER *lpPerformanceCount)
{
  LARGE_INTEGER Frequency;
  NTSTATUS Status;

  Status = NtQueryPerformanceCounter(lpPerformanceCount,
				     &Frequency);
  if (!NT_SUCCESS(Status))
  {
    SetLastErrorByStatus(Status);
    return(FALSE);
  }

  if (Frequency.QuadPart == 0ULL)
  {
    SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
    return(FALSE);
  }

  return(TRUE);
}


/*
 * @implemented
 */
BOOL WINAPI
QueryPerformanceFrequency(LARGE_INTEGER *lpFrequency)
{
  LARGE_INTEGER Count;
  NTSTATUS Status;

  Status = NtQueryPerformanceCounter(&Count,
				     lpFrequency);
  if (!NT_SUCCESS(Status))
  {
    SetLastErrorByStatus(Status);
    return(FALSE);
  }

  if (lpFrequency->QuadPart == 0ULL)
  {
    SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
    return(FALSE);
  }

  return(TRUE);
}

/* EOF */
