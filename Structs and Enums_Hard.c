We live in a big country. This country has touns_count towns in it. Each town has some post offices in which packages are stored and transferred.

Post offices have different inner structure.
 Specifically, each of them has some limitations on the packages it can store - their weight should be between min_weight and max_weight inclusively,
where min_weight and max_weight are fixed for each office.

Packages are stored in some order in the office queue. That means, that they are processed using this order when sending and receiving.

Sometimes two post offices, even in different towns, may organize the following transaction: the first one sends all its packages to the second one. The second one accepts the packages that satisfy the weight condition for the second office and rejects all other ones. These rejected packages return to the first office back and are stored in the same order they were stored before they were sent. The accepted packages move to the tail of the second office's queue in the same order they were stored in the first office.

You should process several queries in your program.
You'll be provided with structures packages, post_office and town. in order to complete this task, you should fill the following functions:

print_all_packages- given the town , print all packages in this town. They should be printed as follows:

Town_name:
    0:
        id_0
        id_1
        ...
    1:
        id_2
        id_3
        ...
    ...
where 0,1  etc are the numbers of post offices and id0,id1 ... are the ids of packages from the 0th post office in the order of its queue,id2 , id3 are from the 1st one etc. There should be one '\t' symbol before post office numbers and two '\t' symbols before the ids.

send_all_acceptable_packages - given the towns source and target and post office indices sources_office_index and target_office_index, manage the transaction described above between the post office # source_office_index in town source and the post office #target_office_index in town target.

town_with_most_packages - given all towns, find the one with the most number of packages in all post offices altogether.
If there are several of them, find the first one from the collection towns.

find_town - given all towns and a string name, find the town with the name name. It's guaranteed that the town exists.

Input Format

First line of the input contains a single integer towns_count.towns_count.  blocks follow, each describing a town.

Every town block contains several lines. On the first line there is a string town_name - the name of the town.
On the second line there is an integer offices_count - the number of the offices in the town.  blocks follow then, each describing an office.

Every office block also contains several lines.
On the first line there are three integers separated by single spaces: packages_count (the number of packages in the office),min_weight  and max_weight (described above). packages_count blocks follow, each describing a package.

Every package block contains exactly two lines. On the first line there is a string  which is an id of the package. On the second line there is an integer weight which is the weight of the package.

Then, there is a single integer quries on the line which is the number of queries.  blocks follow, each describing a query.

Every query block contains several lines.
On the first line there is an integer 1,2  or 3 . If this integer is 1, on the second line there is a string town_name - the name of town for which all packages should be printed.
If this integer is 2, on the second line there are string source_name, integer source_office_index, string target_name and integer target_office_index separated by single spaces.
That means transactions between post office # source_office_index in the town source_name and post office #target_office_index  in the town target_name should be processed.

If the integer is 3, no lines follow and the town with the most number of packages should be found.

Constraints

All integer are between 0 and 10

towns_count >0,offices_count>0

All strings have length <= 5
All towns' names have only uppercase english letters and are unique.
All packages' ids have only lowercase english letters and are unique.
For each post office, min_weigt<=max_weight  .
All queries are valid, that means, towns with the given names always exist, post offices with the given indices always exist.

Output Format

For queries of type , print all packages in the format provided in the problem statement. For queries of type , print "Town with the most number of packages is " on a separate line.

Sample Input 0

2
A
2
2 1 3
a 2
b 3
1 2 4
c 2
B
1
4 1 4
d 1
e 2
f 3
h 4
5
3
2 B 0 A 1
3
1 A
1 B

Sample Output 0

Town with the most number of packages is B
Town with the most number of packages is A
A:
    0:
        a
        b
    1:
        c
        e
        f
        h
B:
    0:
        d
Explanation 0

Before all queries, town B has 4 packages in total, town  A has 3. But after transaction all packages from B's 0th post office go to the 1st post office of A, except package d because it's too light.

/***************************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 6

struct package
{
    char* id;
    int weight;
};

typedef struct package package;

struct post_office
{
    int min_weight;
    int max_weight;
    package* packages;
    int packages_count;
};

typedef struct post_office post_office;

struct town
{
    char* name;
    post_office* offices;
    int offices_count;
};

typedef struct town town;

void print_all_packages(town t)
{
    printf("%s:\n", t.name);
    for (int i = 0; i < t.offices_count; i++) {
        printf("\t%d:\n", i);
        for (int j = 0; j < t.offices[i].packages_count; j++) {
            printf("\t\t%s\n", t.offices[i].packages[j].id);
        }
    }
}

void send_all_acceptable_packages(town* source, int source_office_index, town* target, int target_office_index)
{
    post_office* source_office = &(source->offices[source_office_index]);
    post_office* target_office = &(target->offices[target_office_index]);
    int moved_count = 0;
    for (int i = 0; i < source_office->packages_count; i++) {
        package* pkg = &(source_office->packages[i]);
        if (pkg->weight >= target_office->min_weight && pkg->weight <= target_office->max_weight) {
            target_office->packages = realloc(target_office->packages, (target_office->packages_count + 1) * sizeof(package));
            target_office->packages[target_office->packages_count] = *pkg;
            target_office->packages_count++;
            moved_count++;
        }
    }

    // Remove the moved packages from the source office
    int remaining_count = source_office->packages_count - moved_count;
    package* remaining_packages = malloc(remaining_count * sizeof(package));
    int remaining_index = 0;
    for (int i = 0; i < source_office->packages_count; i++) {
        package* pkg = &(source_office->packages[i]);
        if (!(pkg->weight >= target_office->min_weight && pkg->weight <= target_office->max_weight)) {
            remaining_packages[remaining_index++] = *pkg;
        }
    }

    free(source_office->packages);
    source_office->packages = remaining_packages;
    source_office->packages_count = remaining_count;
}

town town_with_most_packages(town* towns, int towns_count) {
    int max_packages = 0;
    town* most_packages_town = &towns[0];

    for (int i = 0; i < towns_count; i++) {
        int total_packages = 0;
        for (int j = 0; j < towns[i].offices_count; j++) {
            total_packages += towns[i].offices[j].packages_count;
        }
        if (total_packages > max_packages) {
            max_packages = total_packages;
            most_packages_town = &towns[i];
        }
    }

    return *most_packages_town;
}

town* find_town(town* towns, int towns_count, char* name) {
    for (int i = 0; i < towns_count; i++) {
        if (strcmp(towns[i].name, name) == 0) {
            return &towns[i];
        }
    }
    return NULL;

int main() {
    int towns_count;
    scanf("%d", &towns_count);
    town* towns = malloc(sizeof(town) * towns_count);
    for (int i = 0; i < towns_count; i++) {
        towns[i].name = malloc(sizeof(char) * MAX_STRING_LENGTH);
        scanf("%s", towns[i].name);
        scanf("%d", &towns[i].offices_count);
        towns[i].offices = malloc(sizeof(post_office) * towns[i].offices_count);
        for (int j = 0; j < towns[i].offices_count; j++) {
            scanf("%d%d%d", &towns[i].offices[j].packages_count, &towns[i].offices[j].min_weight, &towns[i].offices[j].max_weight);
            towns[i].offices[j].packages = malloc(sizeof(package) * towns[i].offices[j].packages_count);
            for (int k = 0; k < towns[i].offices[j].packages_count; k++) {
                towns[i].offices[j].packages[k].id = malloc(sizeof(char) * MAX_STRING_LENGTH);
                scanf("%s", towns[i].offices[j].packages[k].id);
                scanf("%d", &towns[i].offices[j].packages[k].weight);
            }
        }
    }
    int queries;
    scanf("%d", &queries);
    char town_name[MAX_STRING_LENGTH];
    while (queries--) {
        int type;
        scanf("%d", &type);
        switch (type) {
            case 1:
                scanf("%s", town_name);
                town* t = find_town(towns, towns_count, town_name);
                print_all_packages(*t);
                break;
            case 2:
                scanf("%s", town_name);
                town* source = find_town(towns, towns_count, town_name);
                int source_index;
                scanf("%d", &source_index);
                scanf("%s", town_name);
                town* target = find_town(towns, towns_count, town_name);
                int target_index;
                scanf("%d", &target_index);
                send_all_acceptable_packages(source, source_index, target, target_index);
                break;
            case 3:
                printf("Town with the most number of packages is %s\n", town_with_most_packages(towns, towns_count).name);
                break;
        }
    }
    return 0;
}

