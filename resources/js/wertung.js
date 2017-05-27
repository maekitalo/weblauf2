define(['jquery', 'veranstaltung', 'wettkampf'], function($, veranstaltung, wettkampf) {
    var my = {}

    my.onLoad = function() {
        if (!wettkampf.wid)
            return;

        $('#content').load('html/wertung.html', {},
            function() {
                my.table = $('#wertungenTable').DataTable({
                    ajax: {
                        url: 'wertungen.json',
                        data: { vid: veranstaltung.vid, wid: wettkampf.wid },
                        dataSrc: ''
                    },
                    select: true,
                    columns: [
                        { data: 'rid' },
                        { data: 'name' },
                        { data: 'abhaengig' },
                        { data: 'urkunde' },
                        { data: 'preis' }
                    ],
                    order: [ [0, 'asc'] ]
                });

                my.table.on('select', function (e, dt, type, indexes) {
                    var wertung = dt.row(indexes[0]).data();
                    my.rid = wertung.rid;
                });
            });
    }

    return my;
})
