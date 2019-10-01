sub PrintHTMLHeader
{
    print <<__EOF;

<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN" 
   "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en">

<head>
<link rel='stylesheet' href='/bo.css' />
<link rel='stylesheet' href='local.css' />

<title>www.bioinf.org.uk : Prof. Andrew C.R. Martin's Group at UCL</title>
<meta http-equiv="pragma" content="no-cache" />
<meta http-equiv="expires" content="0" />
<meta http-equiv="Cache-control" content="no-cache" />
<script src='/em.js' type='text/javascript'></script>
</head>

<!-- ******************************************************************* -->

<body>


<div id='header'>
<p>www.bioinf.org.uk : Prof. Andrew C.R. Martin's Group</p>
</div> <!-- header -->
<div id='separator'>
<form method='get' action='http://www.google.com/search' >
<p>
<input type='hidden' name='as_sitesearch' value='bioinf.org.uk' />
<input type='text' name='as_q' size='20' value='Search site' onclick="document.forms[0].as_q.value=''" />
</p>
</form>
</div> <!-- separator -->

<!-- *************** SYSTEM FAILURE  ******************* -->
<!--
<div class='systemfailure'>
<p>Our main server is now up and running again!
</p>
<p>
  Please email us if there are any problems.
</p>
</div>
-->
<!-- *************** END SYSTEM FAILURE  ******************* -->



<div id='mainmenu'>
<!-- Needs full paths since it is access from sub-dirs -->
<ul>
<li><a href="/index.html">Overview</a></li>
<li id='mcurrent'><a href="/abs">Antibodies</a></li>
<li><a href="/servers/">Servers</a></li>
<li><a href="/mutations/">Mutations</a></li>
<li><a href="/software/">Software</a></li>
<li><a href="/group/">Group</a></li>
<li><a href="/sitemap/">Sitemap</a></li>
</ul>
</div> <!-- mainmenu -->
<div id='mainpage'>

<div id='submenu'>
<ul>
<li><a href='/abs/index.html'>Info</a></li>
<li id='current'><a href='/abs/sequences.html'>Sequences</a></li>
<li><a href='/abs/structures.html'>Structures</a></li>
<li><a href='/abs/software.html'>Software</a></li>
<li><a href='/abs/patents/'>Humanization patents</a></li>
<li><a href='/abs/links.html'>Links</a></li>
<li><a href='/abs/awards.html'>Awards</a></li>
</ul>
</div>
<div id='subpage'>


__EOF
}

sub PrintHTMLFooter
{
    print <<__EOF;
</div>
</div>

</div>  <!-- subpage -->
<div class='rsslink'>
<a href='/rss/'><img src='/images/rss-icon.jpg' alt='RSS' width='50' /></a>
</div>
<script src="/lastmodified.js" type='text/javascript'>
</script>
</div>  <!-- mainpage -->

</body>
</html>

__EOF
}

sub ErrorMessage
{
    my($msg1, $msg2) = @_;

    print <<__EOF;
<h2>Error</h2>
<h3>$msg1</h3>

<p>$msg2</p>
__EOF
}

sub ErrorPage
{
    my($msg1, $msg2) = @_;
    PrintHTMLHeader();
    print <<__EOF;
<div id='main'>
<h1>Sequence Analysis</h1>
<div id='maincontent'>&nbsp;
__EOF
    ErrorMessage($msg1, $msg2);
    PrintHTMLFooter();
}

1;
