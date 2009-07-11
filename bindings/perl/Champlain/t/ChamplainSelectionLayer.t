#!/usr/bin/perl

use strict;
use warnings;

use Clutter::TestHelper tests => 51;

use Champlain;
use Data::Dumper;

exit tests();

sub tests {
	test_empty_multiple();
	test_empty_single();

	test_markers_multiple();
	test_markers_single();
	return 0;
}


sub test_empty_multiple {
	my $layer = Champlain::SelectionLayer->new();
	isa_ok($layer, 'Champlain::Layer');

	is($layer->get_selection_mode, 'multiple');
	is($layer->get('selection_mode'), 'multiple');

	is($layer->get_selected, undef, "[empty] get_selected()");

	# In single mode get_selected_markers doesn't work
	is_deeply(
		[$layer->get_selected_markers],
		[],
		"[empty] get_selected_markers()"
	);

	my $count = $layer->count_selected_markers;
	is($count, 0, "[empty] count_selected_markers()");

	my $marker = Champlain::BaseMarker->new();
	ok(!$layer->marker_is_selected($marker), "[empty] marker_is_selected()");

	# Can't be tested but at least they are invoked
	$layer->select($marker);
	$layer->unselect($marker);
	$layer->select_all();
	$layer->unselect_all();

	# Change the selection mode
	$layer->set_selection_mode('single');
	is($layer->get_selection_mode, 'single');

	$layer->set('selection_mode', 'multiple');
	is($layer->get('selection_mode'), 'multiple');

	return 0;
}


sub test_empty_single {
	my $layer = Champlain::SelectionLayer->new();
	isa_ok($layer, 'Champlain::Layer');

	my $notify = 0;
	$layer->signal_connect('notify::selection-mode', sub {
		++$notify;
	});

	is($layer->get_selection_mode, 'multiple');
	is($layer->get('selection_mode'), 'multiple');
	$layer->set_selection_mode('single');
	is($notify, 1, "signal notify::selection-mode emitted");
	is($layer->get_selection_mode, 'single');
	is($layer->get('selection_mode'), 'single');

	is($layer->get_selected, undef, "[empty] get_selected()");

	# In single mode get_selected_markers doesn't work
	is_deeply(
		[$layer->get_selected_markers],
		[],
		"[empty] get_selected_markers()"
	);

	my $count = $layer->count_selected_markers;
	is($count, 0, "[empty] count_selected_markers()");

	my $marker = Champlain::BaseMarker->new();
	ok(!$layer->marker_is_selected($marker), "[empty] marker_is_selected()");

	# Can't be tested but at least they are invoked
	$layer->select($marker);
	$layer->unselect($marker);
	$layer->select_all();
	$layer->unselect_all();

	# Change the selection mode
	$layer->set_selection_mode('multiple');
	is($notify, 2, "signal notify::selection-mode emitted");
	is($layer->get_selection_mode, 'multiple');

	$layer->set('selection_mode', 'single');
	is($notify, 3, "signal notify::selection-mode emitted");
	is($layer->get('selection_mode'), 'single');

	return 0;
}


sub test_markers_multiple {
	my $layer = Champlain::SelectionLayer->new();
	isa_ok($layer, 'Champlain::Layer');


	my @layer_markers = (
		Champlain::BaseMarker->new(),
		Champlain::BaseMarker->new(),
		Champlain::BaseMarker->new(),
		Champlain::BaseMarker->new(),
	);

	# Add the markers and select a few markers
	foreach my $marker (@layer_markers) {
		$layer->add($marker);
	}
	$layer->select($layer_markers[1]);
	$layer->select($layer_markers[3]);


	# This doesn't work in multiple mode
	is($layer->get_selected, undef, "[multiple] get_selected()");


	my @markers;
	@markers = $layer->get_selected_markers;
	is_deeply(\@markers, [$layer_markers[1], $layer_markers[3]], "[multiple] get_selected_markers()");

	my $count = $layer->count_selected_markers;
	is($count, 2, "[multiple] count_selected_markers()");

	my $marker = Champlain::BaseMarker->new();

	# Check wich markers are selected
	ok(!$layer->marker_is_selected($marker), "[multiple] marker_is_selected() maker not in set");
	ok(!$layer->marker_is_selected($layer_markers[0]), "[multiple] marker_is_selected() maker not selected");
	ok(!$layer->marker_is_selected($layer_markers[2]), "[multiple] marker_is_selected() maker not selected");
	ok($layer->marker_is_selected($layer_markers[1]), "[multiple] marker_is_selected() selected");
	ok($layer->marker_is_selected($layer_markers[3]), "[multiple] marker_is_selected() selected");


	# Select a new marker
	$layer->select($marker);
	ok($layer->marker_is_selected($marker), "[multiple] select() maker not in set");
	$count = $layer->count_selected_markers;
	is($count, 3, "[multiple] count_selected_markers() with a new marker");
	is_deeply(
		[ $layer->get_selected_markers ],
		[$layer_markers[1], $layer_markers[3], $marker],
		"[multiple] get_selected_markers()"
	);


	# Select again one of the selected markers, this unselects it
	$layer->select($marker);
	ok(!$layer->marker_is_selected($marker), "[multiple] select() deselects an already selected marker");
	$count = $layer->count_selected_markers;
	is($count, 2, "[multiple] count_selected_markers() with a deselected marker");
	is_deeply(
		[ $layer->get_selected_markers ],
		[$layer_markers[1], $layer_markers[3]],
		"[multiple] get_selected_markers()"
	);


	# Remove a marker
	$layer->unselect($layer_markers[1]);
	$count = $layer->count_selected_markers;
	is($count, 1, "[multiple] count_selected_markers() after unselect()");
	is_deeply(
		[ $layer->get_selected_markers ],
		[$layer_markers[3]],
		"[multiple] get_selected_markers()"
	);

	# Remove all markers
	$layer->unselect_all();
	$count = $layer->count_selected_markers;
	is($count, 0, "[multiple] count_selected_markers() after count_selected_markers()");
	is_deeply(
		[ $layer->get_selected_markers ],
		[],
		"[multiple] get_selected_markers()"
	);


	# Select all markers
	$layer->select_all();
	$count = $layer->count_selected_markers;
	is($count, 4, "[multiple] select_all()");

	$layer->select_all();
	$count = $layer->count_selected_markers;
	is($count, 4, "[multiple] select_all()");

	return 0;
}


sub test_markers_single {
	my $layer = Champlain::SelectionLayer->new();
	isa_ok($layer, 'Champlain::Layer');
	$layer->set_selection_mode('single');


	my @layer_markers = (
		Champlain::BaseMarker->new(),
		Champlain::BaseMarker->new(),
		Champlain::BaseMarker->new(),
		Champlain::BaseMarker->new(),
	);

	# Add the markers
	foreach my $marker (@layer_markers) {
		$layer->add($marker);
	}

	is($layer->count_selected_markers, 0, "[single] count_selected_markers() empty");

	# Select the first marker
	$layer->select($layer_markers[1]);
	is($layer->get_selected, $layer_markers[1], "[single] get_selected()");
	ok($layer->marker_is_selected($layer_markers[1]), "[single] marker_is_selected() selected");

	# Select another marker
	$layer->select($layer_markers[3]);
	is($layer->get_selected, $layer_markers[3], "[single] get_selected() after change");
	ok(!$layer->marker_is_selected($layer_markers[1]), "[single] marker_is_selected() selected");
	ok($layer->marker_is_selected($layer_markers[3]), "[single] marker_is_selected() selected");

	is($layer->count_selected_markers, 1, "[single] count_selected_markers()");

	is_deeply(
		[ $layer->get_selected_markers ],
		[$layer_markers[3]],
		"[single] get_selected_markers()"
	);

	return 0;
}
