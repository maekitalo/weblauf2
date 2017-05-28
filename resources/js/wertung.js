define(['jquery', 'veranstaltung', 'wettkampf'], function($, veranstaltung, wettkampf) {
    var my = {}

    my.onLoad = function() {
        if (!veranstaltung.wid)
            return;

        $('#content').load('html/wertung.html', {},
            function() {
                my.table = $('#wertungenTable').DataTable({
                    ajax: {
                        url: 'wertungen.json',
                        data: { vid: veranstaltung.vid, wid: veranstaltung.wid },
                        dataSrc: ''
                    },
                    select: true,
                    columns: [
                        { data: 'rid' },
                        { data: 'name' },
                        { data: 'abhaengig',
                          render: function(data, type, row, meta) {
                                return row.aw ? row.aw.name : ''; }
                        },
                        { data: 'urkunde' },
                        { data: 'preis' }
                    ],
                    order: [ [0, 'asc'] ]
                });

                my.table.on('select', function (e, dt, type, indexes) {
                    var wertung = dt.row(indexes[0]).data();
                    veranstaltung.selectWertung(wertung);
                });
            });
    }

    return my;
})
