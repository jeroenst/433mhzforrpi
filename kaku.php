<?php
 $qstr = ereg_replace("[^A-Za-z0-9]", " ", $_SERVER['QUERY_STRING']);
 $cmd = "/usr/bin/kaku $qstr";
 exec ($cmd, $output, $execreturnvalue);
 if ($execreturnvalue == 0)
 {
  echo "<HTML><BODY>Ok</BODY></HTML>";
 }
 else
 {
  echo "<HTML><BODY>Fail</BODY></HTML>";
 }
?>