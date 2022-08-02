<h1> Ucode-track-C <h1>

  <h3>All C programs that were developed during the UcodeConnect-TrackC are collected here.</h3>

  <br /> <br />
  <h2> UcodeConnect-Refresh-C </h2>
  <h5>Some tasks that were completed during the UcodeConnect-marathonC.</h5>
  <h5>Total mark 100</h5>
  <h2> UcodeConnect-Libmx-C </h2>
  <h5>Total mark 99</h5>
  <h5>Useful C functions collected in one library</h5>
  <h2> UcodeConnect-Pathfinder-C </h2>
  <h5>Total mark 100</h5>
  <h5>The program finds all the shortest paths between all islands.</h5>

Examples

```
>cat -e example1$
Greenland-Bananal,8$
Fraser-Greenland,10$
Bananal-Fraser,3$
Java-Fraser,5$
>./pathfinder example1 |cat -e
========================================$
Path: Greenland -> Bananal$
Route: Greenland -> Bananal$
Distance: 8$
========================================$
========================================$
Path: Greenland -> Fraser$
Route: Greenland -> Fraser$
Distance: 10$
========================================$
========================================$
Path: Greenland -> Java$
Route: Greenland -> Fraser -> Java$
Distance: 10 + 5 = 15$
========================================$
========================================$
Path: Bananal -> Fraser$
Route: Bananal -> Fraser$
Distance: 3$
========================================$
========================================$
Path: Bananal -> Java$
Route: Bananal -> Fraser -> Java$
Distance: 3 + 5 = 8$
========================================$
========================================$
Path: Fraser -> Java$
Route: Fraser -> Java$Distance: 5
$========================================$
>cat -e example2$
A-B,11$
A-C,10$
B-D,5$
C-D,6$
C-E,15$
D-E,4$
>./pathfinder example2 |cat -e
========================================$
Path: A -> B$
Route: A -> B$
Distance: 11$
========================================$
========================================$
Path: A -> C$
Route: A -> C$
Distance: 10$
========================================$
========================================$
Path: A -> D$
Route: A -> B -> D$
Distance: 11 + 5 = 16$
========================================$
========================================$
Path: A -> D$
Route: A -> C -> D$
Distance: 10 + 6 = 16$
========================================$
========================================$
Path: A -> E$
Route: A -> B -> D -> E$
Distance: 11 + 5 + 4 = 20$
========================================$
========================================$
Path: A -> E$
Route: A -> C -> D -> E$
Distance: 10 + 6 + 4 = 20$
========================================$
========================================$
Path: B -> C$
Route: B -> D -> C$
Distance: 5 + 6 = 11$
========================================$
========================================$
Path: B -> D$
Route: B -> D$
Distance: 5$
========================================$
========================================$
Path: B -> E$
Route: B -> D -> E$
Distance: 5 + 4 = 9$
========================================$
========================================$
Path: C -> D$
Route: C -> D$
Distance: 6$
========================================$
========================================$
Path: C -> E$
Route: C -> D -> E$
Distance: 6 + 4 = 10$
========================================$
========================================$
Path: D -> E$
Route: D -> E$
Distance: 4$
========================================$
  <h2> UcodeConnect-Uls-C </h2>
  <h2> UcodeConnect-Ush-C <h2>
