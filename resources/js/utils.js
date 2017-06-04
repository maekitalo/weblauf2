define(['noty'], function() {
    var my = {}

    my.error = function(msg, timeout)
    {
        if (timeout < 0)
            timeout = null;

        return noty({
            text: msg,
            type: 'error',
            timeout: timeout
        });
    }

    my.warning = function(msg, timeout)
    {
        if (timeout < 0)
            timeout = null;

        return noty({
            text: msg,
            type: 'warning',
            timeout: timeout
        });
    }

    my.information = function(msg, timeout)
    {
        if (!timeout)
            timeout = 5000;
        else if (timeout < 0)
            timeout = null;

        return noty({
            text: msg,
            type: 'information',
            timeout: timeout
        });
    }

    my.notification = function(msg, timeout)
    {
        if (!timeout)
            timeout = 5000;
        else if (timeout < 0)
            timeout = null;

        return noty({
            text: msg,
            type: 'notification',
            timeout: timeout
        });
    }

    my.success = function(msg, timeout)
    {
        if (!timeout)
            timeout = 5000;
        else if (timeout < 0)
            timeout = null;

        return noty({
            text: msg,
            type: 'success',
            timeout: timeout
        });
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

    return my;
})
