#!/acrm/usr/local/bin/perl
#*************************************************************************
#
#   Program:    SAPTF
#   File:       analyze.cgi
#   
#   Version:    V1.5
#   Date:       14.01.10
#   Function:   Sequence analysis plugin tool framework
#   
#   Copyright:  (c) UCL / Dr. Andrew C. R. Martin 2009-2010
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
#   V1.2  18.09.09   Overlib says "Tool help" rather than "Abysis help"
#   V1.3  08.12.09   Configuration of text and help colours through
#                    configuration XML. saptf div added around tools and
#                    results. Added 'slow' (asynchronous) mode
#   V1.4  09.12.09   Added very slow mode
#   V1.5  14.01.10   Fixed some problems with missing config tags
#
#*************************************************************************
use strict;
use XML::DOM;
use CGI;
require 'config.pm';
require 'html.pm';
require 'saptf.pm';

#*************************************************************************
# 23.03.09  Original   By: ACRM
$::linestatus = 1;

my $cgi = new CGI;
print $cgi->header();

if(! -e $::xmlfile)
{
    ErrorPage("Configuration error",
              "The tools file $::xmlfile was not found.<br /> \
Please fix analysis tools config.pm", 1);
}

my $parser = XML::DOM::Parser->new();
my $doc = $parser->parsefile($::xmlfile);

SetDefaultConfig();
ReadConfig($doc);
PrintHTMLHeader();
PrintStart($doc);
PrintToolList($doc);
PrintSeqBoxes($doc);
PrintEnd();
PrintHTMLFooter();

#*************************************************************************
# Prints the textarea boxes for entering sequence data
# 23.03.09  Original   By: ACRM
sub PrintSeqBoxes
{
    my($doc) = @_;
    my($texttag, $text, $id, $display);
    print "<h4>$::config{'datatitle'}</h4>\n<div class='seqinput'>\n";

    foreach my $seqboxtag ($doc->getElementsByTagName('seqbox'))
    {
        $id = $seqboxtag->getAttribute('id');
        if(($texttag = $seqboxtag->getElementsByTagName('text')))
        {
            $text = $texttag->item(0)->getFirstChild->getNodeValue;
        }
        $display = "style='display: inline;'";
        if($seqboxtag->getAttribute('hidden') == 1)
        {
            $display = "style='display: none;'";
        }

        print "\n<div id='$id' $display>\n<p>$text</p>\n";
        print "<textarea cols='60' rows='3' name='$id' class='seqbox'></textarea>\n</div> <!-- sequence box -->\n";
    }
    print "</div> <!-- seqinput -->\n";
}

#*************************************************************************
# Print the radio-buttoned list of available tools
# 23.03.09  Original   By: ACRM
# 08.12.09  Added configuration through <config>
# 09.12.09  If there is only one tool, then no bullets or buttons are shown
# 14.01.10  Additional error checking on missing tags. Missing 
#           <description> tag was breaking the script
sub PrintToolList
{
    my($doc) = @_;
    my $checked = "checked='checked'";

    if(!$::config{'onetool'})
    {
        print "<h4>$::config{'toolstitle'}</h4>\n";
    }
    print "<div class='buttonlist'>\n";

    print "<ul>\n" if(!$::config{'onetool'});
    
    foreach my $seqtooltag ($doc->getElementsByTagName('seqtool'))
    {
        my $inputs         = "[";
        my $text           = "";
        my $exe            = "";
        my $paramlist      = "";
        my $description    = "";
        my @param_ids      = ();
        my @param_types    = ();
        my @param_labels   = ();
        my @param_options  = ();
        my @param_defaults = ();
        my @param_values   = ();
        
        my $pid = $seqtooltag->getAttribute('id');
        $::linestatus = 1;

        foreach my $inputtag ($seqtooltag->getElementsByTagName('input'))
        {
            $inputs .= "\"" . $inputtag->getFirstChild->getNodeValue . "\"";
            $inputs .= ",";
        }
        chop $inputs;
        $inputs .= "]";

        if((my $texttag = $seqtooltag->getElementsByTagName('text')))
        {
            if($texttag->item(0)) # 14.01.10 By: ACRM
            {
                $text = $texttag->item(0)->getFirstChild->getNodeValue;
            }
        }
        if((my $tooltag = $seqtooltag->getElementsByTagName('tool')))
        {
            $tooltag = $tooltag->item(0);
            if($tooltag)        # 14.01.10 By: ACRM
            {
                $exe = $tooltag->getAttribute('exe');
                $paramlist = $tooltag->getAttribute('param');
            }
        }
        if((my $descriptiontag = $seqtooltag->getElementsByTagName('description')))
        {
            if($descriptiontag->item(0)) # 14.01.10 By: ACRM
            {
                $description = $descriptiontag->item(0)->getFirstChild->getNodeValue;
            }
        }
        foreach my $parametertag ($seqtooltag->getElementsByTagName('parameter'))
        {
            push @param_ids,      $parametertag->getAttribute('id');
            push @param_types,    $parametertag->getAttribute('type');
            push @param_labels,   $parametertag->getAttribute('label');
            push @param_options,  $parametertag->getAttribute('options');
            push @param_defaults, $parametertag->getAttribute('default');
            push @param_values,   $parametertag->getAttribute('value');
        }
        
        if(($text ne "") && ($exe ne "") && ($paramlist ne ""))
        {
            if(!$::config{'onetool'})
            {
                print "<li class='buttonlistitem'><input type='radio' name='analysis' value='$pid' $checked onmouseup='ShowOnlyBoxes($inputs);' />$text";
            }
            else
            {
                print "<p><input style='display: none' type='radio' name='analysis' value='$pid' $checked onmouseup='ShowOnlyBoxes($inputs);' />$text";
            }
            $checked = "";
            my $i = 0;
            PrintDescription($description);
            foreach my $id (@param_ids)
            {
                if($i==0)
                {
                    print "<br />\n";
                    print "<div class='buttonlistparams'>\n";
                }
                my $html = BuildOption($pid,
                                       $id, 
                                       $param_types[$i], 
                                       $param_labels[$i], 
                                       $param_options[$i], 
                                       $param_defaults[$i],
                                       $param_values[$i]);
                print $html;
                $i++;
            }
            print "</div>\n" if($i);
            print "</li>\n" if(!$::config{'onetool'});
        }
    }
    if(!$::config{'onetool'})
    {
        print "</ul>\n";
    }
    else
    {
        print "</p>\n";
    }
    print "</div> <!-- buttonlist -->\n";
}

#*************************************************************************
# Print the help text using the Javascript Overlib library
# 23.03.09  Original   By: ACRM
sub PrintDescription
{
    my($description) = @_;

    $description =~ s/^\s+//;
    $description =~ s/\s+$//;
    $description =~ s/\'/&apos;/g;
    $description =~ s/\"/ /g;
    
    if($description ne "")
    {
        print " <a href='javascript:ShowDescription(\"$description\")'><img src='i_help.gif' class='saptfimg' alt='(H)' /></a>\n";
    }
}

#*************************************************************************
# Build and display an option set for a tool. These may be numeric, 
# pull-down menus, radio buttons, etc
# 23.03.09  Original   By: ACRM
sub BuildOption
{
    my($pid, $id, $type, $label, $options, $defaults, $value) = @_;
    my($html, $size, $option, @options);
    $size = 5;

    if($type eq "numeric")
    {
        $html .= $label . ": ";
        $html .= "<input type='text' name='${pid}_$id' value='$defaults' size='$size' />&nbsp;\n";
        $::linestatus = 0;
    }
    elsif($type eq "pulldown")
    {
        $html .= $label . ": ";
        $html .= "<select name='${pid}_$id'>\n";
        @options = split(/,/, $options);
        foreach $option (@options)
        {
            my $optionlc = "\L$option";
            $optionlc =~ s/\s/-/g;
            $html .= "   <option value='$optionlc'>$option</option>\n";
        }
        $html .= "</select>\n";
        $::linestatus = 0;
    }
    elsif($type eq "checkbox")
    {
        $html .= $label . ": ";
        $html .= "<input type='checkbox' name='${pid}_$id' value='$value' ";
        $html .= "checked='checked' " if($defaults == 1);
        $html .= "/>\n";
        $::linestatus = 0;
    }
    elsif($type eq "radio")
    {
        $html .= "<br /> " if($::linestatus == 0);
        $html .= "<input type='radio' name='${pid}_$id' value='$value' ";
        $html .= "checked='checked' " if($defaults == 1);
        $html .= "/> $label<br />\n";
        $::linestatus = 1;
    }
    elsif($type eq "label")
    {
        $html .= "<br /> " if($::linestatus == 0);
        $html .= "<b>$label</b>\n";
        $html .= "<br /> ";
        $::linestatus = 1;
    }
    else
    {
        ErrorPage("Configuration error", 
                  "The sequence tool description file contained an unrecognized parameter type: $type",
                  0);
    }
    return($html);
}

#*************************************************************************
# Print the start of the page and the needed JavaScript. This follows an
# HTML header
# 23.03.09  Original   By: ACRM
# 08.12.09  Added configuration through <config>
sub PrintStart
{
    my($doc) = @_;

    my $boxes = "[";
    foreach my $seqboxtag ($doc->getElementsByTagName('seqbox'))
    {
        my $id = $seqboxtag->getAttribute('id');
        $boxes .= "\"$id\",";
    }
    chop $boxes;
    $boxes .= "]";

    print <<__EOF;
<script type='text/javascript' src='$::overlib/overlib.js'></script>
<script type='text/javascript'>
<!--
   function ShowDescription(text)
   {
     overlib(text, STICKY, CAPTION, '$::overlib{'caption'}', RIGHT, WIDTH, $::overlib{'width'}, FGCOLOR, '$::overlib{'fgcolor'}', BGCOLOR, '$::overlib{'bgcolor'}', CLOSECOLOR, '$::overlib{'closecolor'}', CAPCOLOR, '$::overlib{'capcolor'}', BORDER, 1);
   }
   function HideSeqBoxes() 
   {
      boxes = $boxes;
      for(var i in boxes)
      {
         var ele = document.getElementById(boxes[i]);
         ele.style.display = 'none';
      }
   }
   function ShowSeqBox(obj) 
   {
      var ele = document.getElementById(obj);
      ele.style.display = 'inline';
   }
   function ShowOnlyBoxes(objs)
   {
       HideSeqBoxes();
       for(var i in objs)
       {
           ShowSeqBox(objs[i]);
       }
   }
-->
</script>

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
<h2>$::config{'subtitle'}</h2>

<form action='doanalyze.cgi' method='post'>

__EOF
}

#*************************************************************************
# Print the end of the page including the submit and clear buttons. This
# is followed by a page footer
# 23.03.09  Original   By: ACRM
sub PrintEnd
{
    print <<__EOF;
<p>
<input type='submit' value='Submit' />
<input type='reset' value='Clear Form' />
</p>

</form>
</div> <!-- saptf -->
__EOF
}

