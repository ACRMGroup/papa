#*************************************************************************
#
#   Program:    SAPTF
#   File:       saptf.pm
#   
#   Version:    V1.4
#   Date:       09.12.09
#   Function:   Sequence analysis plugin wrapper
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
#   V1.3  08.12.09   Split out from main code
#   V1.4  09.12.09   Skipped
#
#*************************************************************************
$::version = "1.4";

#*************************************************************************
# Set default configuration options. These can all be overridden in the
# <config> tag in the XML
# 08.12.09  Original   By: ACRM
sub SetDefaultConfig
{
    $::config{'title'} = "Sequence analysis tools";
    $::config{'subtitle'} = "Analyze your sequence";
    $::config{'resultssubtitle'} = "Analysis results...";
    $::config{'toolstitle'} = "Select an analysis tool";
    $::config{'datatitle'} = "Enter your sequence data";
    $::overlib{'caption'} = "SAPTF Help";
    $::overlib{'width'} = 400;
    $::overlib{'fgcolor'} = "#CCCCCC";
    $::overlib{'bgcolor'} = "#92aec7";
    $::overlib{'closecolor'} = "#000000";
    $::overlib{'capcolor'} = "#a03030";
}
#*************************************************************************
# Set the user-specified configuration options from the <config> tag in 
# the XML
# 08.12.09  Original   By: ACRM
sub ReadConfig
{
    my($doc) = @_;
    if((my $configtag=$doc->getElementsByTagName('config')->item(0)))
    {
        if((my $value=$configtag->getAttribute('onetool')))
        {
            $::config{'onetool'} = $value;
        }

        if((my $tag=$configtag->getElementsByTagName('title')->item(0)))
        {
            $::config{'title'} = $tag->getFirstChild->getNodeValue;
        }
        if((my $tag=$configtag->getElementsByTagName('subtitle')->item(0)))
        {
            $::config{'subtitle'} = $tag->getFirstChild->getNodeValue;
        }
        if((my $tag=$configtag->getElementsByTagName('resultssubtitle')->item(0)))
        {
            $::config{'resultssubtitle'} = $tag->getFirstChild->getNodeValue;
        }
        if((my $tag=$configtag->getElementsByTagName('toolstitle')->item(0)))
        {
            $::config{'toolstitle'} = $tag->getFirstChild->getNodeValue;
        }
        if((my $tag=$configtag->getElementsByTagName('datatitle')->item(0)))
        {
            $::config{'datatitle'} = $tag->getFirstChild->getNodeValue;
        }
        if((my $tag=$configtag->getElementsByTagName('overlib')->item(0)))
        {
            if((my $value=$tag->getAttribute('caption')))
            {
                $::overlib{'caption'} = $value;
            }
            if((my $value=$tag->getAttribute('width')))
            {
                $::overlib{'width'} = $value;
            }
            if((my $value=$tag->getAttribute('fgcolor')))
            {
                $::overlib{'fgcolor'} = $value;
            }
            if((my $value=$tag->getAttribute('bgcolor')))
            {
                $::overlib{'bgcolor'} = $value;
            }
            if((my $value=$tag->getAttribute('closecolor')))
            {
                $::overlib{'closecolor'} = $value;
            }
            if((my $value=$tag->getAttribute('capcolor')))
            {
                $::overlib{'capcolor'} = $value;
            }
        }
    }
}


1;
