define(['jquery', 'datatables.net', 'datatables.select'], function($) {
    var my = {}

    my.onLoad = function() {
        $('#content').load('html/veranstaltung.html', {},
            function() {
                my.table = $('#veranstaltungenTable').DataTable({
                    ajax: {
                        url: 'veranstaltungen.json',
                        dataSrc: ''
                    },
                    select: true,
                    columns: [
                        { data: 'vid' },
                        { data: 'datum' },
                        { data: 'name' },
                        { data: 'ort' },
                        { data: 'logo' }
                    ],
                    order: [ [1, 'desc'], [0, 'desc'] ]
                });

                my.table.on('select', function (e, dt, type, indexes) {
                    var veranstaltung = dt.row(indexes[0]).data();
                    my.vid = veranstaltung.vid;
                });
            });
    }

    return my;
})
