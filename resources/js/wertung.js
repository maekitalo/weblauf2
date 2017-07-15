define(['weblauf', 'utils', 'datatables.net', 'datatables.select', 'jquery-ui', 'chosen-js', 'populate'], function(weblauf, utils) {
    var my = {}

    my.onLoad = function() {
        if (!weblauf.wid) {
            utils.warning('kein Wettkampf ausgewählt');
            return;
        }

        $('#content').load('html/wertung.html', {},
            function() {
                $('#wettkampf').wettkampf(function(sel) {
                    sel.val(weblauf.wid)
                           .change(function(ev) {
                                weblauf.selectWettkampf(
                                    sel.val(), function() {
                                        my.table.ajax.reload();
                                    });
                           });
                })

                my.table = $('#wertungenTable').DataTable({
                    ajax: {
                        url: 'wertungen.json',
                        data: function() { return { vid: weblauf.vid, wid: weblauf.wid } },
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
                        { data: 'preis' },
                        { data: 'akStr' }
                    ],
                    order: [0, 'asc']
                });

                my.table.on('click', 'tr', function () {
                    var wertung = my.table.row(this).data();
                    weblauf.selectWertung(wertung);
                });

                var dialog = $('<div/>');

                var editdialogButtons = [
                    {
                        text: 'Ok',
                        click: function() {
                            utils.action('wertung/save', $('form', $(this)).serialize(),
                                function() {
                                    my.table.ajax.reload();
                                });
                            $(this).dialog("close");
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
                    var wertung = data.length > 0 ? data[0] : weblauf.wertung;

                    if (!wertung)
                    {
                        utils.error('keine Wertung ausgewählt', 5000);
                        return;
                    }

                    dialog.load('html/wertung/edit.html', function() {
                        var wertungen = my.table.data();

                        var selAk = $('[name=ak]', dialog);
                        var selNoak = $('[name=noak]', dialog);
                        var selAllak = $('[name=allak]', dialog);
                        $.getJSON('ak.json', function(allAk) {
                            $.each(allAk, function(id, ak) {
                                var sel = (wertung.ak.indexOf(ak.ak) >= 0) ? selAk : selNoak;
                                $('<option>', {
                                    value: ak.ak,
                                    html: ak.bezeichnung
                                }).appendTo(sel);
                                $('<option>', {
                                    value: ak.ak,
                                    html: ak.bezeichnung
                                }).appendTo(selAllak);
                            })
                        });

                        selNoak.chosen();
                        selAllak.chosen();

                        $('[name=abhaengig]', dialog).wertung(function() {
                            dialog.populate(wertung)
                                   .dialog({
                                        width: 700,
                                        height: 500,
                                        appendTo: '#content',
                                        buttons: editdialogButtons
                                   })
                        });

                        $('#akAdd', dialog).click(function(ev) {
                            ev.preventDefault();
                            $('#noak :selected').detach()
                                .appendTo($('#ak'));
                        });
                        $('#akSub', dialog).click(function(ev) {
                            ev.preventDefault();
                            $('#ak :selected').detach()
                                .appendTo($('#noak'));
                        });
                    })
                });
;
                $('#neu').click(function() {
                    dialog.load('html/wertung/edit.html', function() {
                        $(':input[name="vid"]', $(this)).val(weblauf.vid);
                        $(':input[name="wid"]', $(this)).val(weblauf.wid);
                        $(':input[name="rid"]', $(this)).val("0");

                        var wertungen = my.table.data();
                        var sel = $('[name=abhaengig]', dialog);
                        for (var i = 0; i < wertungen.length; ++i) {
                            var r = wertungen[i];
                            $('<option>', {
                                value: r.rid,
                                html: r.name
                            }).appendTo(sel);
                        }

                        $(this).dialog({
                            width: 700,
                            appendTo: '#content',
                            buttons: editdialogButtons
                        })
                    })
                });
;
                $('#loeschen').click(function() {
                    var data = my.table.rows({selected:true}).data();
                    var wertung = data.length > 0 ? data[0] : weblauf.wertung;
                    if (!wertung)
                    {
                        utils.error('keine Wertung ausgewählt', 5000);
                        return;
                    }

                    var d = dialog.html("Wertung <b>" + wertung.name + "</b> wirklich löschen?").dialog({
                        appendTo: '#content',
                        modal: true,
                        buttons: {
                            "ja": function() {
                                utils.action('wertung/del', wertung, function() {
                                    my.table.ajax.reload();
                                    weblauf.selectWertung(null);
                                });
                                $(this).dialog("close")
                            },
                            "nein": function() { $(this).dialog("close") }
                        }
                    });
                });
            });
    }

    return my;
})
