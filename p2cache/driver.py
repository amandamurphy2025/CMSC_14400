#!/usr/bin/python
#
# driver.py - The driver tests the correctness and performance of
#     their transpose function. It runs ./test-trans on three
#     different sized matrices (32x32, 64x64, and 61x67) to test the
#     correctness and performance of the transpose function.
#
# Changelog:
# ----------
# 2023-10-17: Remove part (a). Update to python3

import subprocess;
import re;
import optparse;

#
# computeMissScore - compute the score depending on the number of
# cache misses
#
def computeMissScore(miss, lower, upper, full_score):
    if miss <= lower:
        return full_score
    if miss >= upper:
        return 0

    score = (miss - lower) * 1.0
    range = (upper- lower) * 1.0
    return round((1 - score / range) * full_score, 1)

#
# main - Main function
#
def main():

    # Configure maxscores here
    maxscore= {}
    maxscore['transc'] = 1
    maxscore['trans32'] = 38
    maxscore['transR']  = 38
    maxscore['trans64'] = 24

    # Parse the command line arguments
    p = optparse.OptionParser()
    p.add_option("-A", action="store_true", dest="autograde",
                 help="emit autoresult string for Autolab");
    opts, args = p.parse_args()
    autograde = opts.autograde

    # Check the correctness and performance of the transpose function
    # 32x32 transpose
    print("Testing transpose function")
    print("Running ./test-trans -M 32 -N 32")
    p = subprocess.Popen("./test-trans -M 32 -N 32 | grep TEST_TRANS_RESULTS",
                         shell=True, stdout=subprocess.PIPE)
    stdout_data = p.communicate()[0]
    result32 = re.findall(r'(\d+)', stdout_data.decode())

    # 32x64 transpose
    print("Running ./test-trans -M 32 -N 64")
    p = subprocess.Popen("./test-trans -M 32 -N 64 | grep TEST_TRANS_RESULTS",
                         shell=True, stdout=subprocess.PIPE)
    stdout_data = p.communicate()[0]
    resultR = re.findall(r'(\d+)', stdout_data.decode())

    # 64x64 transpose
    print("Running ./test-trans -M 64 -N 64")
    p = subprocess.Popen("./test-trans -M 64 -N 64 | grep TEST_TRANS_RESULTS",
                         shell=True, stdout=subprocess.PIPE)
    stdout_data = p.communicate()[0]
    result64 = re.findall(r'(\d+)', stdout_data.decode())

    # Compute the scores for each step
    # trans_cscore = int(result32[0]) * int(result64[0]); #* int(result61[0]);
    miss32 = int(result32[1])
    missR  = int(resultR[1])
    miss64 = int(result64[1])
    trans32_score = computeMissScore(miss32,  300,  600, maxscore['trans32']) * int(result32[0])
    transR_score  = computeMissScore(missR,   700, 1000, maxscore['transR']) * int(resultR[0])
    trans64_score = computeMissScore(miss64, 1300, 3000, maxscore['trans64']) * int(result64[0])
    total_score = trans32_score + transR_score + trans64_score

    # Summarize the results
    print("\nCache Lab summary:")
    print("%-22s%8s%10s%12s" % ("", "Points", "Max pts", "Misses"))

    misses = str(miss32)
    if miss32 == 2**31-1 :
        misses = "invalid"
    print("%-22s%8.1f%10d%12s" % ("Trans perf 32x32", trans32_score,
                                  maxscore['trans32'], misses))

    misses = str(missR)
    if missR == 2**31-1 :
        misses = "invalid"
    print("%-22s%8.1f%10d%12s" % ("Trans perf 32x64", transR_score,
                                  maxscore['transR'], misses))

    misses = str(miss64)
    if miss64 == 2**31-1 :
        misses = "invalid"
    print("%-22s%8.1f%10d%12s" % ("Trans perf 64x64", trans64_score,
                                  maxscore['trans64'], misses))

    print("%22s%8.1f%10d" % ("Total points", total_score,
                             maxscore['trans32'] +
                             maxscore['transR'] +
                             maxscore['trans64']))

    # Emit autoresult string for Autolab if called with -A option
    if autograde:
        # autoresult="%.1f:%d:%d:%d" % (total_score, miss32, miss64, miss61)
        autoresult="%.1f:%d:%d" % (total_score, miss32, miss64)
        print("\nAUTORESULT_STRING=%s" % autoresult)


# execute main only if called as a script
if __name__ == "__main__":
    main()

