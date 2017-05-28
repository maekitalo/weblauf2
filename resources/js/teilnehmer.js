define(['jquery', 'veranstaltung', 'datatables.net'], function($, veranstaltung) {
    var my = {}

    my.onLoad = function() {
        $('#content').load('html/teilnehmer.html', {},
            function() {
                my.table = $('#teilnehmerTable').DataTable({
                    serverSide: true,
                    ajax: {
                        url: 'personen.json',
                        data: { vid: veranstaltung.vid }
                    },
                    columns: [
                        { data: 'nachname' },
                        { data: 'vorname' },
                        { data: 'verein' },
                        { data: 'jahrgang' },
                        { data: 'startnummer' }
                    ],
                    order: [ [ 4, 'desc' ], [ 0, 'desc'], [1, 'desc'] ]
                });
            });
    }

    return my;
})
