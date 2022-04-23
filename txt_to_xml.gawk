{
    print "<tileset name=\"" $1 "\">"
    print "    <firstgid value=\"8\"/>"
    print "    <tilewidth value=\"16\"/>"
    print "    <tileheight value=\"16\"/>"
    print "    <numColumns value=\"1\"/>"
    print "    <numRows value=\"1\"/>"
    print "    <spacing value=\"0\"/>"
    print "    <margin value=\"0\"/>"
    print "    <source value=\"./assets/drawable/map/" $1 ".png\"/>"
    print "</tileset>"
}