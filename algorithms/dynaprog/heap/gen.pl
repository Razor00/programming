#!/usr/bin/perl
@arr=();
$line;
%data = ();
while(<>)
{
	@arr=split(//);
#	print @arr,"\n";		
	for( $i=0; $i< $#arr; $i++) {
		++$data{$arr[$i]};
#		print $arr[$i], " ",$data{$arr[$i]},"\n";
	}
}

foreach $key (sort keys(%data)) {
	print $key," ",$data{$key},"\n";
}
