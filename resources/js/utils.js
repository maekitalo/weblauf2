define(['Noty', 'jquery'], function(Noty) {
    var my = {}

    my.error = function(msg, timeout)
    {
        new Noty(
        {
            type: 'error',
            text: msg,
            timeout: timeout < 0 ? null : timeout
        }).show();
    }

    my.warning = function(msg, timeout)
    {
        new Noty(
        {
            type: 'warning',
            text: msg,
            timeout: timeout < 0 ? null : timeout
        }).show();
    }

    my.information = function(msg, timeout)
    {
        new Noty(
        {
            type: 'info',
            text: msg,
            timeout: timeout == null ? 5000 : timeout
        }).show();
    }

    my.notification = function(msg, timeout)
    {
        new Noty(
        {
            type: 'notification',
            text: msg,
            timeout: timeout == null ? 5000 : timeout
        }).show();
    }

    my.success = function(msg, timeout)
    {
        new Noty(
        {
            type: 'success',
            text: msg,
            timeout: timeout == null ? 5000 : timeout
        }).show();
    }

    my.processNotification = function(n)
    {
        if (n.severity === 0)
            my.success(n.message, n.timeout);
        else if (n.severity === 1)
            my.notification(n.message, n.timeout);
        else if (n.severity === 2)
            my.information(n.message, n.timeout);
        else if (n.severity === 3)
            my.warning(n.message, n.timeout);
        else
            my.error(n.message, n.timeout);
    }

    my.processNotifications = function(notifications)
    {
        for (var i = 0; i < notifications.length; ++i)
            my.processNotification(notifications[i]);
    }

    my.action = function(url, data, successFn, failureFn)
    {
        $.post(url + ".action", data,
            function(data, textStatus, jqXHR)
            {
                if (data.success)
                {
                    if (successFn)
                        successFn(data, textStatus, jqXHR);
                }
                else if (data.notLoggedIn)
                {
                    warning("session timed out");
                    setTimeout(function() {
                        window.location = '/';
                    }, 3000);
                }
                else
                {
                    if (failureFn)
                        failureFn(data, textStatus, jqXHR);
                }

                my.processNotifications(data.notifications);

            }, 'json');
    }

    my.action = function(url, data, successFn, failureFn) {
        $.post(url + ".action", data,
            function(data, textStatus, jqXHR)
            {
                if (data.success)
                {
                    if (successFn)
                        successFn(data, textStatus, jqXHR);
                }
                {
                    if (failureFn)
                        failureFn(data, textStatus, jqXHR);
                }

                my.processNotifications(data.notifications);

            }, 'json');
    }

    return my;
})
