requirejs.config({
    baseUrl: 'js',
    paths: {
        'jquery': '../jquery/dist/jquery',
        'datatables.net': '../datatables.net/js/jquery.dataTables',
        'datatables.select': '../datatables.net-select/js/dataTables.select',
        'datatables.fixedcolumns': '../datatables.net-fixedcolumns/js/dataTables.fixedColumns',
        'jquery-ui': '../jquery-ui-1.12.1.custom/jquery-ui',
        'Noty': '../noty/lib/noty'
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

requirejs(['weblauf', 'utils', 'jquery'], function(weblauf, utils) {

    $('#nav a').click(function(ev) {
        ev.preventDefault();
        weblauf.goToScreen($(this).attr('href'));
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
