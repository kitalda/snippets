#!/usr/bin/env perl

use warnings;
use strict;

my ( $createmode ) = @ARGV;
my $testdir = "./tests";

if( defined($createmode) ) {
    if($createmode cmp "create") {
	print "Brug:\n";
	print "\tcheck.pl         - tester om dit programs output matcher .out-filerne\n";
	print "\tcheck.pl create  - laver .out-filerne forfra (sletter de eksisterende filer!)\n";
	exit();
    }
    $createmode=1;
}

# print "$testdir/tests.tst";
open(TESTS, "$testdir/tests.tst");


my $koereplan;
my $startst;
my $slutst;

while (<TESTS>) {

    /([\w\d]+)\.in\s+\"(.+)\"\s+\"(.+)\"/ && do {
	$koereplan="$testdir/$1";
	$startst=$2;
	$slutst=$3;

	# print $koereplan."\t".$startst."\t".$slutst."\n";

	open(RUN, "./travelplanning $koereplan.in '$startst' '$slutst' |");
	my $cost=0;
	while(<RUN>) {
	    /^(\d+)\s+(\d+)$/ && do {
		$cost=$1+$2*15;
	    }
	};
	
	#print "Cost fra programmet: $cost";

	my $outfile="$koereplan.$startst.$slutst.out";
	# print $outfile."\n";
	if($createmode) {
	    open(OUT, ">$outfile") or die "Couldn't open '$outfile' for writing";
	} else {
	    open(IN, "<$outfile") or die "Couldn't open '$outfile' for reading";
	}
	if($createmode) {
	    print OUT "$cost\n";
	} else {
	    my $facit=<IN>;
	    if($facit cmp "$cost\n") {
		chomp $facit;
		print "ERROR: $koereplan.in $startst $slutst gav $cost og facit er $facit.\n";
		#last;
	    } else {
		chomp $facit;
		print "SUCCES: $koereplan.in $startst $slutst gav $cost og facit er $facit.\n";
	    };
	};
    };
}
