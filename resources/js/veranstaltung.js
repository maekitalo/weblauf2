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
                    if (my.vid !== veranstaltung.vid)
                    {
                        my.veranstaltung = veranstaltung;
                        my.vid = veranstaltung.vid;
                        my.wid = null;
                        my.rid = null;
                        my.wettkampf = null;
                        my.wertung = null;
                        document.title = veranstaltung.name;
                    }
                });
            });
    }

    my.selectWettkampf = function(wettkampf, cb) {
        if ($.isNumeric(wettkampf)) {
            $.getJSON('wettkampf.json', { vid: my.vid, wid: wettkampf },
                function (w) { my.selectWettkampf(w, cb); });
        }
        else if (my.wid !== wettkampf.wid) {
            my.wettkampf = wettkampf;
            my.wid = wettkampf.wid;
            my.wertung = null;
            my.rid = null;
            if (cb)
                cb();
        }
    }

    my.selectWertung = function(wertung, cb) {
        if ($.isNumeric(wertung)) {
            $.getJSON('wertung.json', { vid: my.vid, wid: my.wid, rid: wertung },
                function(w)  { my.selectWertung(w, cb) });
        }
        else if (my.rid !== wertung.rid) {
            my.wertung = wertung;
            my.rid = wertung.rid;
            if (cb)
                cb();
        }
    }

    return my;
})
