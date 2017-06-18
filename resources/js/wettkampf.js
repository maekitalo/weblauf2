define(['weblauf', 'utils', 'jquery-ui', 'datatables.net', 'datatables.select', 'populate'], function(weblauf, utils) {
    var my = {}

    my.onLoad = function() {
        if (!weblauf.vid) {
            utils.warning('keine Veranstaltung ausgewählt');
            return;
        }

        $('#content').load('html/wettkampf.html', {},
            function() {
                my.table = $('#wettkaempfeTable').DataTable({
                    ajax: {
                        url: 'wettkaempfe.json',
                        data: { vid: weblauf.vid },
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
                    weblauf.selectWettkampf(wettkampf);
                });

                var dialog = $('<div/>');

                var editdialogButtons = [
                    {
                        text: 'Ok',
                        click: function() {
                            utils.action('wettkampf/save', $('form', $(this)).serialize(),
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
                    var wettkampf = data.length > 0 ? data[0] : weblauf.wettkampf;

                    if (!wettkampf)
                    {
                        utils.error('keine Wertung ausgewählt', 5000);
                        return;
                    }

                    dialog.load('html/wettkampf/edit.html', function() {
                        $(this).populate(wettkampf)
                               .dialog({
                                    width: 500,
                                    appendTo: ('#content'),
                                    buttons: editdialogButtons
                               })
                    })
                });

                $('#neu').click(function() {
                    dialog.load('html/wettkampf/edit.html', function() {
                        $(':input[name="vid"]', $(this)).val(weblauf.vid);
                        $(':input[name="wid"]', $(this)).val("0");
                        $(this).dialog({
                            width: 500,
                            appendTo: ('#content'),
                            buttons: editdialogButtons
                        })
                    })
                });

                $('#loeschen').click(function() {
                    var data = my.table.rows({selected:true}).data();
                    var wettkampf = data.length > 0 ? data[0] : weblauf.wettkampf;
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
                                utils.action('wettkampf/del', wettkampf,
                                    function() {
                                        my.table.ajax.reload();
                                        weblauf.selectWettkampf(null);
                                    });
                                $(this).dialog("close")
                            },
                            "nein": function() { $(this).dialog("close") }
                        }
                    });
                })

                $('#wertung').click(function() {
                    weblauf.goToScreen('wertung');
                })
            });
    }

    return my;
})
