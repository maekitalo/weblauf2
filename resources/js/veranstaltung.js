define(['jquery', 'utils', 'datatables.net'], function($, utils) {
    var my = {}

    my.onLoad = function() {
        $('#content').load('html/veranstaltung.html', {},
            function() {
                my.table = $('#veranstaltungenTable').DataTable({
                    ajax: {
                        url: 'veranstaltungen.json',
                        dataSrc: ''
                    },
                    columns: [
                        { data: 'vid' },
                        { data: 'datum' },
                        { data: 'name' },
                        { data: 'ort' },
                        { data: 'logo' }
                    ],
                    order: [ [1, 'desc'], [0, 'desc'] ]
                });

                my.table.on('click', 'tr', function () {
                    var veranstaltung = my.table.row(this).data();
                    if (my.vid !== veranstaltung.vid)
                    {
                        my.veranstaltung = veranstaltung;
                        my.vid = veranstaltung.vid;
                        my.wid = null;
                        my.rid = null;
                        my.wettkampf = null;
                        my.wertung = null;
                        document.title = veranstaltung.name;
                        utils.information('Veranstaltung <i>' + veranstaltung.name + '</i> ausgewählt');
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
            utils.information('Wettkampf <i>' + wettkampf.name + '</i> ausgewählt');
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
            utils.information('Wertung <i>' + wertung.name + '</i> ausgewählt');
            if (cb)
                cb();
        }
    }

    return my;
})
