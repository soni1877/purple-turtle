/*
 * Inria Assignment
 * By Amit Kumar (soni1877@gmail.com)
 * Date: 2-July-2014
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

void getInput(int *csize, int *tracks_no, multimap<int, int> *track_length);
int side1Track(int csize, int tracks_no, multimap<int, int> track_length, vector<int> *side1);
int side2Track(int csize, int tracks_no, multimap<int, int> track_length, vector<int> side1, vector<int> *side2);
void printResult(int csize, int tracks_no, vector<int> side1, vector<int> side2, int t1, int t2);

int main()
{
    int csize = 0, tracks_no = 0, t1 = 0, t2 = 0;
    multimap<int, int> track_length;

    /* Get the input from the file */
    getInput(&csize, &tracks_no, &track_length);

    /* Get the list of side-1 tracks */
    vector<int> side1;
    t1 = side1Track(csize, tracks_no, track_length, &side1);

    /* Get the list of side-2 tracks */
    vector<int> side2;
    t2 = side2Track(csize, tracks_no, track_length, side1, &side2);
    
    /* Print the Result */
    printResult(csize, tracks_no, side1, side2, t1, t2);
}

/*
 * This routine will print the result as which all tracks should
 * be putup on each side of the cassette along with total number
 * of tracks, cassette size and elapsed time on each side.
 */
void printResult(int csize, int tracks_no, vector<int> side1, vector<int> side2, int t1, int t2)
{
    cout << endl << tracks_no << " tracks on a C-" << csize << " cassette" << endl;

    /* Print side-1 information */
    cout << "Side 1 ->";
    for(vector<int>::iterator iter = side1.begin(); iter != side1.end(); ++iter)
        cout << " " << *iter;
    cout << endl;
    cout << "Side 1 elapsed time: " << (t1 / 60) << ":" << (t1 % 60) << endl;

    /* Print side-2 information */
    cout << "Side 2 ->";
    for(vector<int>::iterator iter = side2.begin(); iter != side2.end(); ++iter)
        cout << " " << *iter;
    cout << endl;
    cout << "Side 2 elapsed time: " << (t2 / 60) << ":" << (t2 % 60) << endl;
}

/*
 * This routine will get the input from a file as first argument
 * will be the cassette size, second will be number of tracks and 
 * rest will be the time of each tracks in minutes
 */
void getInput(int *csize, int *tracks_no, multimap<int, int> *track_length)
{
    int i, min, sec;
    char time[10];

    cin >> *csize >> *tracks_no;

    for (i = 1; i <= *tracks_no; i++)
    {
        char *end;
        cin >> time;

        min = strtol(time, &end, 10);
        *end++;
        sec = strtol(end, &end, 10);
        track_length->insert(make_pair(min * 60 + sec, i));
    }
}

/*
 * This routine will get the list of tracks which can be placed on
 * side-1 of the cassette. It will pick the tracks in decending
 * order of their length. ie. the longest track will be selected
 * first and so on.
 * return type -> int (total used size)
 */
int side1Track(int csize, int tracks_no, multimap<int, int> track_length, vector<int> *side1)
{
    int total_size = (csize * 60) / 2; 
    int used_size = 0;
  
    for(multimap<int, int>::reverse_iterator iter = track_length.rbegin(); iter != track_length.rend(); ++iter)
    {
        if(used_size == total_size)
            break;

        if(total_size >= used_size + iter->first)
        {
            used_size = used_size + iter->first;
            side1->push_back(iter->second);
        }
    }
    return used_size;
}

/* 
 * This routine will get the list of tracks which can be placed on
 * side-2 of the cassette. It will pick the tracks in the similar
 * way it picked for side-1 along with one more check that the song
 * should not be placed already in side-1 :)
 * return type -> int (total used size)
 */
int side2Track(int csize, int tracks_no, multimap<int, int> track_length, vector<int> side1, vector<int> *side2)
{
    int total_size = (csize * 60) / 2;
    int used_size = 0;

    for(multimap<int, int>::reverse_iterator iter = track_length.rbegin(); iter != track_length.rend(); ++iter)
    {
        if(used_size == total_size)
            break;

        if((total_size >= used_size + iter->first) && (find(side1.begin(), side1.end(), iter->second) == side1.end()))
        {
            used_size = used_size + iter->first;
            side2->push_back(iter->second);
        }
    }
    return used_size;
}
