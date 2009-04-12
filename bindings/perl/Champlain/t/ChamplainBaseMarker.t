#!/usr/bin/perl

use strict;
use warnings;

use Clutter::TestHelper tests => 5;

use Champlain;


exit tests();


sub tests {
	my $marker = Champlain::BaseMarker->new();
	isa_ok($marker, 'Champlain::BaseMarker');

	my ($latitude, $longitude) = $marker->get('latitude', 'longitude');
	is($latitude, 0.0, "Initial latitude is at 0.0");
	is($longitude, 0.0, "Initial longitude is at 0.0");

	$marker->set_position(20.0, 40.0);
	($latitude, $longitude) = $marker->get('latitude', 'longitude');
	is($latitude, 20.0, "set_position() changed the latitude");
	is($longitude, 40.0, "set_position() changed the longitude");

	return 0;
}
