define(['jquery', 'utils', 'datatables.net', 'datatables.select', 'jquery-ui', 'populate'], function($, utils) {
    var my = {}

    var dialog = $('<div/>');

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
                    select: 'single',
                    order: [ [1, 'desc'], [0, 'desc'] ]
                });

                my.table.on('click', 'tr', function () {
                    var veranstaltung = my.table.row(this).data();
                    my.selectVeranstaltung(veranstaltung, function() {
                        utils.information('Veranstaltung <i>' + veranstaltung.name + '</i> ausgewählt');
                    });
                });

                var editdialogButtons = [
                                        {
                                            text: 'Ok',
                                            click: function() {
                                                utils.action('veranstaltung/save', $('form', $(this)).serialize());
                                                $(this).close();
                                                my.table.ajax.reload();
                                            }
                                        },
                                        {
                                            text: 'cancel',
                                            click: function() {
                                                $(this).close();
                                            }
                                        }
                                    ]

                $('#bearbeiten').click(function() {
                    var data = my.table.rows({selected:true}).data();
                    var veranstaltung = data.length > 0 ? data[0] : my.veranstaltung;
                    if (!veranstaltung)
                    {
                        utils.error('keine Veranstaltung ausgewählt', 5000);
                        return;
                    }

                    dialog.load('html/veranstaltung/edit.html', function() {
                        $(':input[name="datum"]', $(this)).datepicker({ dateFormat: 'yy-mm-dd'});
                        $(this).populate(veranstaltung)
                               .dialog({
                                    buttons: editdialogButtons
                                })
                    });
                });

                $('#neu').click(function() {
                    dialog.load('html/veranstaltung/edit.html', function() {
                        $(':input[name="vid"]', $(this)).val("0");
                        $(':input[name="datum"]', $(this)).datepicker({ dateFormat: 'yy-mm-dd'});
                        $(this).dialog({
                                    buttons: editdialogButtons
                                })
                    })
                });

                $('#loeschen').click(function() {
                    var data = my.table.rows({selected:true}).data();
                    var veranstaltung = data.length > 0 ? data[0] : my.veranstaltung;
                    if (!veranstaltung)
                    {
                        utils.error('keine Veranstaltung ausgewählt', 5000);
                        return;
                    }

                    dialog.html("Veranstaltung <b>" + veranstaltung.name + "</b> wirklich löschen?").dialog({
                        modal: true,
                        buttons: {
                            "ja": function() {
                                utils.action('veranstaltung/del', veranstaltung);
                                $(this).close()
                                my.table.ajax.reload();
                                my.wettkampf = null;
                                my.wid = null;
                                my.wertung = null;
                                my.rid = null;
                                document.title = "";
                            },
                            "nein": function() { $(this).close() }
                        }
                    });
                });
            });
    }

    my.selectVeranstaltung = function(veranstaltung, cb) {
        if ($.isNumeric(veranstaltung)) {
            $.getJSON('veranstaltung.json', { vid: veranstaltung },
                function (v) { my.selectVeranstaltung(v, cb); });
        }
        else if (my.vid !== veranstaltung.vid)
        {
            my.veranstaltung = veranstaltung;
            my.vid = veranstaltung.vid;
            my.wid = null;
            my.rid = null;
            my.wettkampf = null;
            my.wertung = null;
            document.title = veranstaltung.name;
            if (cb)
                cb(wettkampf);
        }
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
                cb(wettkampf);
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
                cb(wertung);
        }
    }

    return my;
})
