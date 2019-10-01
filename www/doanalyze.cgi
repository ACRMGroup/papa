#!/acrm/usr/local/bin/perl
#*************************************************************************
#
#   Program:    SAPTF
#   File:       doanalyze.cgi
#   
#   Version:    V1.4
#   Date:       09.12.09
#   Function:   Sequence analysis plugin tool framework
#   
#   Copyright:  (c) UCL / Dr. Andrew C. R. Martin 2009
#   Author:     Dr. Andrew C. R. Martin
#   Address:    Biomolecular Structure & Modelling Unit,
#               Department of Biochemistry & Molecular Biology,
#               University College,
#               Gower Street,
#               London.
#               WC1E 6BT.
#   EMail:      andrew@bioinf.org.uk
#   Web:        http://www.bioinf.org.uk/
#               
#               
#*************************************************************************
#
#   This program is not in the public domain, but it may be copied
#   according to the conditions laid out in the accompanying file
#   COPYING.DOC
#
#   The code may be modified as required, but any modifications must be
#   documented so that the person responsible can be identified. If 
#   someone else breaks this code, I don't want to be blamed for code 
#   that does not work! 
#
#   The code may not be sold commercially or included as part of a 
#   commercial product except as described in the file COPYING.DOC.
#
#*************************************************************************
#
#   Description:
#   ============
#
#*************************************************************************
#
#   Usage:
#   ======
#
#*************************************************************************
#
#   Revision History:
#   =================
#   V1.0  23.03.09   Original
#   V1.1  01.09.09   use strict cleanup
#   V1.2  18.09.09   Add support for plaintext attribute
#   V1.3  08.12.09   Configuration of text and help colours through
#                    configuration XML. saptf div added around tools and
#                    results. Added 'slow' (asynchronous) mode
#   V1.4  09.12.09   Added very slow mode
#
#*************************************************************************
##### NOTE! use strict stops eval working for XML-defined functions  #####
# use strict;
##### NOTE! use strict stops eval working for XML-defined functions  #####
#*************************************************************************
use XML::DOM;
use CGI;
require 'config.pm';
require 'html.pm';
require 'saptf.pm';

#*************************************************************************
# 23.03.09  Original   By: ACRM
my $parser = XML::DOM::Parser->new();
my $doc = $parser->parsefile($::xmlfile);
my $cgi = new CGI;
print $cgi->header();

$::fcount = 0;

SetDefaultConfig();
ReadConfig($doc);
PrintHTMLHeader();
PrintStart();
my ($exe, $plaintext, $slow) = HandleCGI($cgi, $doc);
RunProgram($exe, $plaintext, $slow);
PrintEnd();
PrintHTMLFooter();

#*************************************************************************
# Prints the start of the page after the header
# 23.03.09  Original   By: ACRM
# 08.12.09  Added configuration through <config>
sub PrintStart
{
    print <<__EOF;
<div id='main'>
<h1>$::config{'title'}</h1>
<div id='maincontent'>&nbsp;
<div id='saptf'>
__EOF

    if($::debug)
    {
        print "<p style='color: #FF0000'>SAPTF DEBUG VERSION $::version</p>\n";
    }

    print <<__EOF;
<h2>$::config{'resultssubtitle'}</h2>

__EOF
}

#*************************************************************************
# End the page - a footer will be added
# 23.03.09  Original   By: ACRM
sub PrintEnd
{
    print "</div> <!-- saptf -->\n";
    print "\n";
}

#*************************************************************************
# Checks whether a parameter is in the list of allowed parameters
# 23.03.09  Original   By: ACRM
sub IsValidParam
{
    my($exe, $param, @params) = @_;
    my $pname;
    $pname = $exe . "_" . $param;
    foreach my $p (@params)
    {
        if($pname eq $p)
        {
            return(1);
        }
    }
    return(0);
}

#*************************************************************************
# Does the main work of handling the CGI input, checkingf parameters are
# valid and constructing the command line for the program to be run.
# 23.03.09  Original   By: ACRM
sub HandleCGI
{
    my($cgi, $doc) = @_;
    my($exe, $paramlist, @params, $value, $q, $r, $plaintext, $slow);

    my($pid) = $cgi->param('analysis');
    ($exe, $paramlist, $plaintext, $slow, @params) = GetDetails($pid, $doc);
    my @plist = split(' ', $paramlist);

    foreach my $p (@plist)         # Work through list of expected parameters
    {
        if($p =~ /(.*)\((.*)\)/)          # Parameter contents to be placed into a file
        {
            $r = $1;
            $q = $2;

            $value = "";
            if(defined($cgi->param("${pid}_$q")))        # For program-specific things
            {
                $value = $cgi->param("${pid}_$q");
            }
            elsif(defined($cgi->param($q)))              # For global things
            {
                $value = $cgi->param($q);
            }

            if($r ne "")        # A function has been specified so pass data through that
            {
                $value = Manipulate($value, $r, $doc);
            }

            if($value ne "")
            {
                my $fnm = "/tmp/saptf_$$.$::fcount.dat";
                $::fcount++;
                open(FILE, ">$fnm") || ErrorMessage("File error", "Unable to write temporary file: $fnm");
                print FILE "$value\n";
                close FILE;
                $exe .= " $fnm";
            }
        }
        else                    # Normal parameters
        {
            if(defined($cgi->param("${pid}_$p")))        # For program-specific things
            {
                my $val = $cgi->param("${pid}_$p");
                if($p =~ /seq/)
                {
                    $val =~ s/\s//g;
                }
                $exe .= " " . $val;
            }
            elsif(defined($cgi->param($p)))              # For global things
            {
                my $val = $cgi->param($p);
                if($p =~ /seq/)
                {
                    $val =~ s/\s//g;
                }
                $exe .= " " . $val;
            }
            else
            {
                # If it's a valid parameter, then it is undefined and therefore 
                # should just be blank (i.e. nothing to append). Otherwise it is
                # not a valid parameter, but just a bit of text to add to the
                # command line.
                if(!IsValidParam($pid, $p, @params))
                {
                    $exe .= " " . $p;
                }
            }
        }
    }
    return($exe, $plaintext, $slow);
}

#*************************************************************************
# Manipulates the sequence using a function specified within the XML if
# required
# 23.03.09  Original   By: ACRM
sub Manipulate
{
    my($value, $fname, $doc) = @_;
    my($function, $result);
    $value =~ s/[\n\r]//g;
    $function = GetFunction($doc, $fname);
    print STDERR "<span style='color: #FF0000'>$function</span>\n" if($::debug);
    $result = eval("$fname($value); $function");
    ErrorMessage("Configuration Error", 
                 "XML-defined function failed: $fname($value)") if($result eq "");
    return($result);
}

#*************************************************************************
# Writes a CGI script to be run if this tool is run in slow (delayed) mode
# The CGI script deletes itself when run so no cleanup is needed
# 08.12.09 Original   By: ACRM
sub WriteCGI
{
    my($exe, $plaintext, $slow) = @_;
    my $docroot = $::docroot;
    my $tmpurl;

    if($slow == 1)
    {
        $tmpurl  = "$::htmltmpurl/saptf_$$.cgi";
        my $tmpfile = $docroot . $tmpurl;
        if(open(CGIFILE, ">$tmpfile"))
        {
            print CGIFILE '#!' . "$::perlexe\n";
            print CGIFILE 'use CGI;' . "\n";
            print CGIFILE '$| = 1;' . "\n";
            print CGIFILE 'my $result = `' . $exe . '`;' . "\n";
            print CGIFILE 'my $cgi = new CGI;' . "\n";
            print CGIFILE "sleep 2;\n" if($::debug);
            print CGIFILE 'print $cgi->header();' . "\n";
            print CGIFILE 'print "<pre>\n";' . "\n" if($plaintext);
            print CGIFILE 'print $result;' . "\n";
            print CGIFILE 'print "</pre>\n";' . "\n" if($plaintext);
            print CGIFILE 'unlink "' . $tmpfile . '";' . "\n" if(!$::debug);
            close CGIFILE;
            `chmod a+x $tmpfile`;
        }
    }
    else
    {
        $tmpurl  = "$::htmltmpurl/saptf_$$.html";
        my $tmphtml   = $docroot . $tmpurl;
        my $tmpscript = $docroot . "$::htmltmpurl/saptf_$$.pl";
        if(open(CGIFILE, ">$tmpscript"))
        {
            # First write an empty results file with an HTTP header to
            # tell the browser not to cache the file
            if(open(RESULTFILE, ">$tmphtml"))
            {
                print RESULTFILE <<__EOF;
<html>
<head>
<meta http-equiv="cache-control" content="no-cache">
<meta http-equiv="pragma" content="no-cache">
<meta http-equiv="expires" content="Mon, 22 Jul 2002 11:12:01 GMT">
</head>
<body>
<p>&nbsp;</p>
</body>
</html>
__EOF
                close(RESULTFILE);
            }
            else
            {
                ErrorMessage("Server Error",
                             "Could not write temporary results file");
            }

            print CGIFILE '#!' . "$::perlexe\n";
            print CGIFILE '$| = 1;' . "\n";
            print CGIFILE 'my $result = `' . $exe . '`;' . "\n";
            print CGIFILE "sleep 180;\n" if($::debug);
            print CGIFILE 'if(open(HTMLFILE,">' . $tmphtml . '")) {' . "\n";
            print CGIFILE '   print HTMLFILE "<pre>\n";' . "\n" if($plaintext);
            print CGIFILE '   print HTMLFILE $result;' . "\n";
            print CGIFILE '   print HTMLFILE "</pre>\n";' . "\n" if($plaintext);
            print CGIFILE '   print HTMLFILE "\n<!-- SAPTF_EOF -->\n\n";' . "\n";
            print CGIFILE '   close HTMLFILE;' . "\n";
            print CGIFILE '}' . "\n";
            close CGIFILE;
            `chmod a+x $tmpscript`;
            `nohup $tmpscript &>/dev/null &`;
        }
    }
    return($tmpurl);
}

#*************************************************************************
# Does the work of running the program and returning the results, wrapping
# them in <pre> tags if plaintext is specified. This is simple for normal
# programs, but for 'slow' programs it writes a separate CGI scrpit and
# returns the AJAX code to obtain these results. 
# 08.12.09 Original   By: ACRM
# 09.12.09 Modified for 'very slow' code
sub RunProgram
{
    my($exe, $plaintext, $slow) = @_;

    print "<p style='color: #FF0000'>Running $exe</p>\n" if($::debug);
    print "<div id='saptf_results'>\n";
    if($slow == 0)
    {
        print "<pre>\n" if($plaintext);
        print `$exe`;
        print "</pre>\n" if($plaintext);
    }
    elsif($slow == 1)
    {
        my $cgiscript = WriteCGI($exe, $plaintext, $slow);
        WriteSlowAjax($cgiscript);
    }
    else
    {
        my $cgiscript = WriteCGI($exe, $plaintext, $slow);
        WriteVerySlowAjax($cgiscript, $slow);
    }
    print "</div> <!-- saptf_results -->\n";
}

#*************************************************************************
# This writes the 'wait' throbber and an empty div to display the final
# results. It also writes the AJAX code to go and get results from a
# CGI file. It does this immediately so will time out if the program is
# too slow.
# 09.12.09  Original   By: ACRM
sub WriteSlowAjax
{
    my ($cgiscript) = @_;

    print <<__EOF;
<div id='saptfwait'>
<p><img src='throbber.gif' />Please wait...</p>
</div> <!-- saptfwait -->

<div id='saptfslow' style='display: none'>
</div> <!-- saptfslow -->

<script type='text/javascript'>
var gRequest = null;

function createRequest() 
{
   var req = null;
   try 
   {
      req = new XMLHttpRequest();
   }
   catch (trymicrosoft) 
   {
      try 
      {
         req = new ActiveXObject('Msxml2.XMLHTTP');
      }
      catch (othermicrosoft) 
      {
         try 
         {
            req = new ActiveXObject('Microsoft.XMLHTTP');
         }
         catch (failed)
         {
            req = null;
         }
      }
   }

   return(req);
}

function DisplayResult()
{
   gRequest = createRequest();
   if (gRequest==null)
   {
      alert ('Browser does not support HTTP Request');
      return;
   } 
   var url="$cgiscript";
   gRequest.open('GET',url,true);
   gRequest.onreadystatechange=updatePage;
   gRequest.send(null);
}

function updatePage() 
{ 
   if (gRequest.readyState==4 || gRequest.readyState=='complete')
   { 
      var content = gRequest.responseText;

      var saptfslowcontentElement = document.getElementById('saptfslow');
      saptfslowcontentElement.innerHTML = content;

      var saptfslow = document.getElementById('saptfslow');
      saptfslow.style.display='inline';

      var saptfwait = document.getElementById('saptfwait');
      saptfwait.style.display='none';
   } 
} 

window.onload=function()
{
   DisplayResult();
}
</script>

__EOF
}

#*************************************************************************
# This writes the 'wait' throbber and an empty div to display the final
# results. It also writes the AJAX code to go keep trying an HTML file
# until that file contains the text SAPTF_EOF. When it does so, it 
# displays the results and hides the throbber. This will cope however
# long the program runs for. The code re-tries grabbing the page every
# minute.
# 09.12.09  Original   By: ACRM
sub WriteVerySlowAjax
{
    my ($cgiscript, $slow) = @_;

    print <<__EOF;
<div id='saptfwait'>
<p><img src='throbber.gif' />Please wait (this may take up to $slow minutes: <span id='saptfremaining'>$slow</span> minutes remaining)...</p>
</div> <!-- saptfwait -->

<div id='saptfslow' style='display: none'>
</div> <!-- saptfslow -->

<script type='text/javascript'>
var gRequest = null;
var gIntervalID = 0;
var gTimeOut = (4 * $slow) + 1;

function createRequest() 
{
   var req = null;
   try 
   {
      req = new XMLHttpRequest();
   }
   catch (trymicrosoft) 
   {
      try 
      {
         req = new ActiveXObject('Msxml2.XMLHTTP');
      }
      catch (othermicrosoft) 
      {
         try 
         {
            req = new ActiveXObject('Microsoft.XMLHTTP');
         }
         catch (failed)
         {
            req = null;
         }
      }
   }

   return(req);
}

function RepeatDisplayResult()
{
    DisplayResult();
    gIntervalID = setInterval("DisplayResult()", 15000);
}

function DisplayResult()
{
   gRequest = createRequest();
   if (gRequest==null)
   {
      alert ('Browser does not support HTTP Request');
      return;
   } 
   var url="$cgiscript";
   // Note we use POST not GET as this stops IE from caching!
   gRequest.open('POST',url,true);
   gRequest.onreadystatechange=updatePage;
   gRequest.send(null);
}

function clearText(el) {
    if (el != null) {
        if (el.childNodes) {
            for (var i = 0; i < el.childNodes.length; i++) {
                var childNode = el.childNodes[i];
                el.removeChild(childNode);
            }
        }
    }
}

function replaceText(el, text) {
    if (el != null) {
        clearText(el);
        var newNode = document.createTextNode(text);
        el.appendChild(newNode);
    }
}

function updatePage() 
{ 
   if (gRequest.readyState==4 || gRequest.readyState=='complete')
   { 
      var content = gRequest.responseText;

      if(content.indexOf("SAPTF_EOF") > (-1))
      {
          var saptfslowcontentElement = document.getElementById('saptfslow');
          saptfslowcontentElement.innerHTML = content;

          var saptfslow = document.getElementById('saptfslow');
          saptfslow.style.display='inline';

          var saptfwait = document.getElementById('saptfwait');
          saptfwait.style.display='none';

          clearInterval(gIntervalID);
      }
      else
      {
          if(--gTimeOut == 0)
          {
              var saptfslowcontentElement = document.getElementById('saptfslow');
              saptfslowcontentElement.innerHTML = "<p><b>Error:</b> The process has timed out</p>";

              var saptfslow = document.getElementById('saptfslow');
              saptfslow.style.display='inline';

              var saptfwait = document.getElementById('saptfwait');
              saptfwait.style.display='none';

              clearInterval(gIntervalID);
          }
          else
          {
              var saptfremainingElement = document.getElementById('saptfremaining');
              replaceText(saptfremainingElement, (gTimeOut/4));
          }
      }
   } 
} 

window.onload=function()
{
   RepeatDisplayResult();
}
</script>

__EOF
}

#*************************************************************************
# Gets the details for a tool including its parameter list, and whether it 
# returns plain text or should be run in slow (asynchronous) mode
# 23.03.09  Original   By: ACRM
# 18.09.09  Added plaintext
# 08.12.09  Added slow
sub GetDetails
{
    my($program, $doc) = @_;
    my($exe, $paramlist, @params, $seqtooltag, $pid, $tooltag, 
       $parametertag, $plaintext, $slow);

    $plaintext = 0;
    $slow = 0;

    foreach $seqtooltag ($doc->getElementsByTagName('seqtool'))
    {
        $pid = $seqtooltag->getAttribute('id');
        if($pid eq $program)
        {
            if(($tooltag = $seqtooltag->getElementsByTagName('tool')))
            {
                $tooltag = $tooltag->item(0);
                $exe = $tooltag->getAttribute('exe');
                $paramlist = $tooltag->getAttribute('param');
                $plaintext = $tooltag->getAttribute('plaintext');
                $slow      = $tooltag->getAttribute('slow');
            }
            foreach $parametertag ($seqtooltag->getElementsByTagName('parameter'))
            {
                push @params, $pid . "_" . $parametertag->getAttribute('id');
            }
            last;
        }
    }
    return($exe, $paramlist, $plaintext, $slow, @params);
}

#*************************************************************************
# Gets a function for manipulating the sequence defined in the XML
# 23.03.09  Original   By: ACRM
sub GetFunction
{
    my($doc, $fname) = @_;
    foreach my $functiontag ($doc->getElementsByTagName('function'))
    {
        my $name = $functiontag->getAttribute('name');
        if($name eq $fname)
        {
            return($functiontag->getFirstChild->getNodeValue);
        }
    }
    ErrorMessage("Configuration Error", 
                 "XML specifies a non-defined function: $::xmlfile");
}
