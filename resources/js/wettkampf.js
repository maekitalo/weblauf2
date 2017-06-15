define(['jquery', 'veranstaltung', 'utils', 'datatables.net', 'datatables.select', 'jquery-ui', 'populate'], function($, veranstaltung, utils) {
    var my = {}

    my.onLoad = function() {
        if (!veranstaltung.vid)
            return;

        $('#content').load('html/wettkampf.html', {},
            function() {
                my.table = $('#wettkaempfeTable').DataTable({
                    ajax: {
                        url: 'wettkaempfe.json',
                        data: { vid: veranstaltung.vid },
                        dataSrc: ''
                    },
                    select: true,
                    columns: [
                        { data: 'wid' },
                        { data: 'name' },
                        { data: 'art' },
                        { data: 'staVon' },
                        { data: 'staBis' },
                        { data: 'startzeit' }
                    ],
                    order: [ [5, 'asc'], [0, 'asc'] ]
                });

                my.table.on('click', 'tr', function () {
                    var wettkampf = my.table.row(this).data();
                    veranstaltung.selectWettkampf(wettkampf);
                });

                var dialog = $('<div/>');

                var editdialogButtons = [
                    {
                        text: 'Ok',
                        click: function() {
                            utils.action('wettkampf/save', $('form', $(this)).serialize());
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
                    var wettkampf = data.length > 0 ? data[0] : veranstaltung.wettkampf;

                    if (!wettkampf)
                    {
                        utils.error('keine Wertung ausgewählt', 5000);
                        return;
                    }

                    dialog.load('html/wettkampf/edit.html', function() {
                        $(this).populate(wettkampf)
                               .dialog({
                                    appendTo: ('#content'),
                                    buttons: editdialogButtons
                               })
                    })
                });

                $('#neu').click(function() {
                    dialog.load('html/wettkampf/edit.html', function() {
                        $(':input[name="vid"]', $(this)).val(veranstaltung.vid);
                        $(':input[name="wid"]', $(this)).val("0");
                        $(this).dialog({
                            appendTo: ('#content'),
                            buttons: editdialogButtons
                        })
                    })
                });

                $('#loeschen').click(function() {
                    var data = my.table.rows({selected:true}).data();
                    var wettkampf = data.length > 0 ? data[0] : veranstaltung.wettkampf;
                    if (!wettkampf)
                    {
                        utils.error('keine Wettkampf ausgewählt', 5000);
                        return;
                    }

                    var d = dialog.html("Wettkampf <b>" + wettkampf.name + "</b> wirklich löschen?").dialog({
                        appendTo: ('#content'),
                        modal: true,
                        buttons: {
                            "ja": function() {
                                utils.action('wettkampf/del', wettkampf);
                                $(this).dialog("close")
                                my.table.ajax.reload();
                                veranstaltung.selectWettkampf(null);
                            },
                            "nein": function() { $(this).dialog("close") }
                        }
                    });
                })

                $('#wertung').click(function() {
                    if (!veranstaltung.wettkampf)
                    {
                        utils.error('keine Wettkampf ausgewählt', 5000);
                        return;
                    }
                    utils.goToScreen('wertung');
                })
            });
    }

    return my;
})
