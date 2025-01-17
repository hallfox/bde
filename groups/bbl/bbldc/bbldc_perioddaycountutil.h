// bbldc_perioddaycountutil.h                                         -*-C++-*-
#ifndef INCLUDED_BBLDC_PERIODDAYCOUNTUTIL
#define INCLUDED_BBLDC_PERIODDAYCOUNTUTIL

#include <bsls_ident.h>
BSLS_IDENT("$Id: $")

//@PURPOSE: Support for day-count calculations of 'enum'-specified conventions.
//
//@CLASSES:
//  bbldc::PeriodDayCountUtil: 'enum'-specified day-count calculations
//
//@SEE_ALSO: bbldc_daycountconvention, bbldc_periodicmaactualactual
//
//@DESCRIPTION: This component provides a 'struct',
// 'bbldc::PeriodDayCountUtil', that defines a suite of date-related functions
// used to compute the day count and the year fraction between two dates as
// prescribed by an enumerated day-count convention.  Specifically, the
// 'daysDiff' and 'yearsDiff' methods defined in 'bbldc::PeriodDayCountUtil'
// take a trailing 'DayCountConvention::Enum' argument indicating which
// particular period-based day-count convention to apply.
//
///Usage
///-----
// This section illustrates intended use of this component.
//
///Example 1: Computing Day Count and Year Fraction
/// - - - - - - - - - - - - - - - - - - - - - - - -
// The following snippets of code illustrate how to use
// 'bbldc::PeriodDayCountUtil' methods.  First, create two 'bdlt::Date'
// variables, 'd1' and 'd2':
//..
//  const bdlt::Date d1(2003, 10, 19);
//  const bdlt::Date d2(2003, 12, 31);
//..
// Then, create a schedule of period dates, 'sched', corresponding to a
// quarterly payment ('periodYearDiff == 0.25'):
//..
//  bsl::vector<bdlt::Date> sched;
//  sched.push_back(bdlt::Date(2003, 10, 1));
//  sched.push_back(bdlt::Date(2004,  1, 1));
//..
// Now, compute the day count between 'd1' and 'd2' according to the ICMA
// Actual/Actual day-count convention:
//..
//  const int daysDiff = bbldc::PeriodDayCountUtil::daysDiff(
//                     d1,
//                     d2,
//                     bbldc::DayCountConvention::e_PERIOD_ICMA_ACTUAL_ACTUAL);
//  assert(73 == daysDiff);
//..
// Finally, compute the year fraction between the two dates according to the
// ICMA Actual/Actual day-count convention:
//..
//  const double yearsDiff = bbldc::PeriodDayCountUtil::yearsDiff(
//                     d1,
//                     d2,
//                     sched,
//                     0.25,
//                     bbldc::DayCountConvention::e_PERIOD_ICMA_ACTUAL_ACTUAL);
//  // Need fuzzy comparison since 'yearsDiff' is a 'double'.
//  assert(yearsDiff > 0.1983 && yearsDiff < 0.1985);
//..

#include <bblscm_version.h>

#include <bbldc_daycountconvention.h>

#include <bdlt_date.h>

#include <bsls_libraryfeatures.h>

#include <bsl_vector.h>

#ifdef BSLS_LIBRARYFEATURES_HAS_CPP17_PMR
# include <memory_resource>
#endif

#include <vector>

namespace BloombergLP {
namespace bbldc {

                        // =========================
                        // struct PeriodDayCountUtil
                        // =========================

struct PeriodDayCountUtil {
    // This 'struct' provides a namespace for a suite of pure functions that
    // compute values based on dates according to enumerated day-count
    // conventions.

  private:
    // PRIVATE CLASS METHODS
    static double yearsDiffImp(const bdlt::Date&         beginDate,
                               const bdlt::Date&         endDate,
                               const bdlt::Date         *periodDateBegin,
                               const bdlt::Date         *periodDateEnd,
                               double                    periodYearDiff,
                               DayCountConvention::Enum  convention);
        // Return the (signed fractional) number of years between the specified
        // 'beginDate' and 'endDate' according to the specified day-count
        // 'convention' with periods starting on the specified range
        // '[ periodDateBegin, periodDateEnd )' values and each period having a
        // duration of the specified 'periodYearDiff' years (e.g., 0.25 for
        // quarterly periods).  If 'beginDate <= endDate' then the result is
        // non-negative.  The behavior is undefined unless
        // 'periodDateEnd - periodDateBegin >= 2', the values contained in the
        // range are unique and sorted from minimum to maximum,
        // 'min(beginDate, endDate) >= *periodDateBegin',
        // 'max(beginDate, endDate) <= *(periodDateEnd - 1)', and
        // 'isSupported(convention)'.  Note that reversing the order of
        // 'beginDate' and 'endDate' negates the result; specifically,
        // '|yearsDiff(b,e,pd,pyd,c) + yearsDiff(e,b,pd,pyd,c)| <= 1.0e-15' for
        // all dates 'b' and 'e', periods 'pd', and year fraction per period
        // 'pyd'.

  public:
    // CLASS METHODS
    static int daysDiff(const bdlt::Date&        beginDate,
                        const bdlt::Date&        endDate,
                        DayCountConvention::Enum convention);
        // Return the (signed) number of days between the specified 'beginDate'
        // and 'endDate' according to the specified day-count 'convention'.  If
        // 'beginDate <= endDate' then the result is non-negative.  The
        // behavior is undefined unless 'isSupported(convention)'.  Note that
        // reversing the order of 'beginDate' and 'endDate' negates the result.

    static bool isSupported(DayCountConvention::Enum convention);
        // Return 'true' if the specified 'convention' is valid for use in
        // 'daysDiff' and 'yearsDiff', and 'false' otherwise.

    static double yearsDiff(const bdlt::Date&                   beginDate,
                            const bdlt::Date&                   endDate,
                            const bsl::vector<bdlt::Date>&      periodDate,
                            double                              periodYearDiff,
                            DayCountConvention::Enum            convention);
    static double yearsDiff(const bdlt::Date&                   beginDate,
                            const bdlt::Date&                   endDate,
                            const std::vector<bdlt::Date>&      periodDate,
                            double                              periodYearDiff,
                            DayCountConvention::Enum            convention);
#ifdef BSLS_LIBRARYFEATURES_HAS_CPP17_PMR
    static double yearsDiff(const bdlt::Date&                   beginDate,
                            const bdlt::Date&                   endDate,
                            const std::pmr::vector<bdlt::Date>& periodDate,
                            double                              periodYearDiff,
                            DayCountConvention::Enum            convention);
#endif
        // Return the (signed fractional) number of years between the specified
        // 'beginDate' and 'endDate' according to the specified day-count
        // 'convention' with periods starting on the specified 'periodDate'
        // values and each period having a duration of the specified
        // 'periodYearDiff' years (e.g., 0.25 for quarterly periods).  If
        // 'beginDate <= endDate' then the result is non-negative.  The
        // behavior is undefined unless 'periodDate.size() >= 2', the values
        // contained in 'periodDate' are unique and sorted from minimum to
        // maximum, 'min(beginDate, endDate) >= periodDate.front()',
        // 'max(beginDate, endDate) <= periodDate.back()', and
        // 'isSupported(convention)'.  Note that reversing the order of
        // 'beginDate' and 'endDate' negates the result; specifically,
        // '|yearsDiff(b,e,pd,pyd,c) + yearsDiff(e,b,pd,pyd,c)| <= 1.0e-15' for
        // all dates 'b' and 'e', periods 'pd', and year fraction per period
        // 'pyd'.
};

// ============================================================================
//                             INLINE DEFINITIONS
// ============================================================================

                        // -------------------------
                        // struct PeriodDayCountUtil
                        // -------------------------

// CLASS METHODS
inline
double PeriodDayCountUtil::yearsDiff(
                                 const bdlt::Date&              beginDate,
                                 const bdlt::Date&              endDate,
                                 const bsl::vector<bdlt::Date>& periodDate,
                                 double                         periodYearDiff,
                                 DayCountConvention::Enum       convention)
{
    return yearsDiffImp(beginDate,
                        endDate,
                        periodDate.data(),
                        periodDate.data() + periodDate.size(),
                        periodYearDiff,
                        convention);
}

inline
double PeriodDayCountUtil::yearsDiff(
                                 const bdlt::Date&              beginDate,
                                 const bdlt::Date&              endDate,
                                 const std::vector<bdlt::Date>& periodDate,
                                 double                         periodYearDiff,
                                 DayCountConvention::Enum       convention)
{
    // Some implmentations of 'std::vector', notably Aix and Solaris, do not
    // provide the 'data' accessor.

    const bdlt::Date *begin = periodDate.empty() ? 0 : &*periodDate.begin();
    const bdlt::Date *end   = begin + periodDate.size();

    return yearsDiffImp(beginDate,
                        endDate,
                        begin,
                        end,
                        periodYearDiff,
                        convention);
}

#ifdef BSLS_LIBRARYFEATURES_HAS_CPP17_PMR
inline
double PeriodDayCountUtil::yearsDiff(
                            const bdlt::Date&                   beginDate,
                            const bdlt::Date&                   endDate,
                            const std::pmr::vector<bdlt::Date>& periodDate,
                            double                              periodYearDiff,
                            DayCountConvention::Enum            convention)
{
    // This function is defined here to avoid having to include
    // 'memory_resource' in the .h file.

    return yearsDiffImp(beginDate,
                        endDate,
                        periodDate.data(),
                        periodDate.data() + periodDate.size(),
                        periodYearDiff,
                        convention);
}
#endif

}  // close package namespace
}  // close enterprise namespace

#endif

// ----------------------------------------------------------------------------
// Copyright 2015 Bloomberg Finance L.P.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ----------------------------- END-OF-FILE ----------------------------------
