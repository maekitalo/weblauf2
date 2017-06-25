define(['weblauf', 'utils', 'jquery', 'datatables.net', 'datatables.select', 'jquery-ui', 'populate'], function(weblauf, utils) {
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
                    weblauf.selectVeranstaltung(veranstaltung);
                });

                var dialog = $('<div/>');

                var editdialogButtons = [
                    {
                        text: 'Ok',
                        click: function() {
                            utils.action('veranstaltung/save', $('form', $(this)).serialize(),
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
                                    appendTo: '#content',
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
                                    appendTo: '#content',
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
                        appendTo: '#content',
                        buttons: {
                            "ja": function() {
                                utils.action('veranstaltung/del', veranstaltung,
                                    function() {
                                        my.table.ajax.reload();
                                    });
                                $(this).dialog("close")
                                document.title = "";
                                my.selectVeranstaltung();
                            },
                            "nein": function() { $(this).dialog("close") }
                        }
                    });
                });

                $('#wettkampf').click(function() {
                    weblauf.goToScreen('wettkampf');
                });
            });
    }

    return my;
})
