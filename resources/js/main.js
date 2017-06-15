requirejs.config({
    baseUrl: 'js',
    paths: {
        'jquery': 'jquery-3.2.1',
        'datatables.net': '../DataTables-1.10.15/media/js/jquery.dataTables',
        'datatables.select': '../DataTables-1.10.15/extensions/Select/js/dataTables.select',
        'datatables.fixedcolumns': '../DataTables-1.10.15/extensions/FixedColumns/js/dataTables.fixedColumns',
        'jquery-ui': '../jquery-ui-1.12.1.custom/jquery-ui',
        'Noty': '../noty-3.1.0/lib/noty'
    },

    shim: {
        'jquery': {
            exports: '$'
        },
        'jquery-ui': {
            deps: ['jquery']
        }
    }
})

requirejs(['jquery', 'utils'], function($, utils) {

    $('#nav a').click(function(ev) {
        ev.preventDefault();
        utils.goToScreen($(this).attr('href'));
    })

    $("#nav li:has(ul)").hover(function(){
        $(this).find("ul").slideDown();
    }, function(){
        $(this).find("ul").hide();
    });

    $(document).ajaxError(function(event, xhr, settings, thrownError) {
        console.log("ajaxError", event, xhr, settings, thrownError);
        if (xhr.readyState == 4)
            utils.error(thrownError ? thrownError : xhr.statusText);
    });

    require.onError = function(err) {
        console.log(err);
        utils.error(err.message);
        throw err;
    }
});
