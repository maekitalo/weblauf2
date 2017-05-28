define(['jquery', 'veranstaltung'], function($, veranstaltung) {
    var my = {}

    my.onLoad = function() {
        if (!veranstaltung.vid)
            return;

        $('#content').load('html/wettkampf.html', {},
            function() {
                my.table = $('#wettkaempfeTable').DataTable({
                    ajax: {
                        url: 'wettkaempfe.json',
                        data: { vid: veranstaltung.vid },
                        dataSrc: ''
                    },
                    select: true,
                    columns: [
                        { data: 'wid' },
                        { data: 'name' },
                        { data: 'art' },
                        { data: 'staVon' },
                        { data: 'staBis' },
                        { data: 'startzeit' }
                    ],
                    order: [ [5, 'asc'], [0, 'asc'] ]
                });

                my.table.on('select', function (e, dt, type, indexes) {
                    var wettkampf = dt.row(indexes[0]).data();
                    veranstaltung.selectWettkampf(wettkampf);
                });
            });
    }

    return my;
})
