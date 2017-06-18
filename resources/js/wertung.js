define(['weblauf', 'utils', 'datatables.net', 'datatables.select', 'jquery-ui', 'populate'], function(weblauf, utils) {
    var my = {}

    my.onLoad = function() {
        if (!weblauf.wid) {
            utils.warning('kein Wettkampf ausgewählt');
            return;
        }

        $('#content').load('html/wertung.html', {},
            function() {
                $('#wettkampf').wettkampf(function() {
                        $(this).val(weblauf.wid)
                               .change(function(ev) {
                                    weblauf.selectWettkampf(
                                        $(this).val(), function() {
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
                        $('[name=abhaengig]', dialog).wertung(function() {
                            dialog.populate(wertung)
                                   .dialog({
                                        width: 700,
                                        appendTo: ('#content'),
                                        buttons: editdialogButtons
                                   })
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
                            $('<option>').val(r.rid).text(r.name).appendTo(sel);
                        }

                        $(this).dialog({
                            width: 700,
                            appendTo: ('#content'),
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
                        appendTo: ('#content'),
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
