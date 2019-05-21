#! /opt/local/bin/perl -w


$/=" ";

open A, $ARGV[0] or die "cannot open $ARGV[0]";
open B, $ARGV[1] or die "cannot open $ARGV[1]";

while ($a = <A>)
{
    $b = <B>;

    print "**$a** : **$b**\n";

    die "count mismatch" unless defined $b;

    $rms += ($a-$b)**2;
    $count++;
}

die "count mismatch" if defined ($b = <B>);

print "rms: ", sqrt($rms)/$count, "\n";

    

