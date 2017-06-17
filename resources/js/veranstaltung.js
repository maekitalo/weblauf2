define(['jquery', 'utils', 'datatables.net', 'datatables.select', 'jquery-ui', 'populate'], function($, utils) {
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
                    select: 'single',
                    order: [ [1, 'desc'], [0, 'desc'] ]
                });

                my.table.on('click', 'tr', function () {
                    var veranstaltung = my.table.row(this).data();
                    my.selectVeranstaltung(veranstaltung, function() {
                        utils.information('Veranstaltung <i>' + veranstaltung.name + '</i> ausgewählt');
                    });
                });

                var dialog = $('<div/>');

                var editdialogButtons = [
                    {
                        text: 'Ok',
                        click: function() {
                            utils.action('veranstaltung/save', $('form', $(this)).serialize());
                            $(this).dialog("close");
                            my.table.ajax.reload();
                        }
                    },
                    {
                        text: 'cancel',
                        click: function() {
                            $(this).dialog("close");
                        }
                    }
                ];

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
                                    width: 500,
                                    appendTo: ('#content'),
                                    buttons: editdialogButtons
                                })
                    });
                });

                $('#neu').click(function() {
                    dialog.load('html/veranstaltung/edit.html', function() {
                        $(':input[name="vid"]', $(this)).val("0");
                        $(':input[name="datum"]', $(this)).datepicker({ dateFormat: 'yy-mm-dd'});
                        $(this).dialog({
                                    width: 500,
                                    appendTo: ('#content'),
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
                        appendTo: ('#content'),
                        buttons: {
                            "ja": function() {
                                utils.action('veranstaltung/del', veranstaltung);
                                $(this).dialog("close")
                                document.title = "";
                                my.selectVeranstaltung();
                                my.table.ajax.reload();
                            },
                            "nein": function() { $(this).dialog("close") }
                        }
                    });
                });

                $('#wettkampf').click(function() {
                    utils.goToScreen('wettkampf');
                });
            });
    }

    my.selectVeranstaltung = function(veranstaltung, cb) {
        if (!veranstaltung) {
            my.veranstaltung = null;
            my.vid = null;
            my.selectWettkampf(null, cb);
        }
        else if ($.isNumeric(veranstaltung)) {
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
        if (!wettkampf)
        {
            my.wettkampf = null;
            my.wid = null;
            my.selectWertung(null, cb);
        }
        else if ($.isNumeric(wettkampf)) {
            $.getJSON('wettkampf.json', { vid: my.vid, wid: wettkampf },
                function (w) { my.selectWettkampf(w, cb); });
        }
        else if (my.wid !== wettkampf.wid) {
            my.wettkampf = wettkampf;
            my.wid = wettkampf.wid;
            my.selectWertung(null);
            utils.information('Wettkampf <i>' + wettkampf.name + '</i> ausgewählt');
            if (cb)
                cb(wettkampf);
        }
    }

    my.selectWertung = function(wertung, cb) {
        if (!wertung)
        {
            my.wertung = null;
            my.rid = null;
            if (cb)
                cb();
        }
        else if ($.isNumeric(wertung)) {
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
