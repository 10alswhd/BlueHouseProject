<?php namespace AIQ\Services;
use Illuminate\Support\Facades\Cache;
use Illuminate\Support\Facades\Config;
use AIQ\Models\User;
use AIQ\Models\Event;
use Carbon\Carbon;
use Lang;
use Log;
class GoogleCalendar {
    protected $client;
    protected $service;
    function __construct() {
        /* Get config variables */
        $this->client = new \Google_Client();
        $this->client->setApplicationName("AIQ-CRM");
        $this->client->setClientId(Config::get('google.calendar.client_id'));
        $this->client->setClientSecret(Config::get('google.calendar.client_secret'));
        $this->client->setRedirectUri(Config::get('google.calendar.redirect_uri'));
        $this->client->setAccessType('offline');
        $this->client->addScope("https://www.googleapis.com/auth/calendar");
        //
        //
        $this->service = new \Google_Service_Calendar($this->client);
    }
    public function createAuthUrl($api_token = null) {
        return $this->client->createAuthUrl();
    }
    public function pushEvent(User $seller, Event $event)
    {
        //Compruebo que esté logueado en calendar
        $this->loggingCalendar($seller);
        $summary = Lang::get('events.reason.'.$event->reason).' a '.$event->company->name;
        $description = $event->note;
        $description .= ($event->status)? ' (Evento realizado)':' (Evento NO realizado)';
        //Colores: ID 10 es verde. ID 5 es amarillo.
        //TODO: Agregar el IdColor en la tabla de eventos.
        $color = ($event->status)? '10': '5';
        if($event->allday) {
            $start = array(
                'date' => (new Carbon($event->date))->format('Y-m-d'),
                'timeZone' => Config::get('app.timezone'),
            );
            $end = array(
                'date' => (new Carbon($event->date))->format('Y-m-d'),
                'timeZone' => Config::get('app.timezone'),
            );
        } else {
            $start = array(
                'dateTime' => (new Carbon($event->date))->toRfc3339String(),
                'timeZone' => Config::get('app.timezone'),
            );
            $end = array(
                'dateTime' => (new Carbon($event->date))->addHours(1)->toRfc3339String(),
                'timeZone' => Config::get('app.timezone'),
            );
        }
        //Pushiar algun evento
        $event = new \Google_Service_Calendar_Event(array(
            'summary' => $summary,
            //'location' => '800 Howard St., San Francisco, CA 94103',
            'description'   => $description,
            'colorId'       => $color,
            'start'         => $start,
            'end'           => $end,
            'attendees'     => '',/*array(
                array('email' => 'lpage@example.com'),
                array('email' => 'sbrin@example.com'),
            ),*/
            'reminders'     => array(
                'useDefault'    => FALSE,
                'overrides'     => array(
                        array('method' => 'email', 'minutes' => 24 * 60),
                        array('method' => 'popup', 'minutes' => 120),
                        array('method' => 'popup', 'minutes' => 10),
                ),
            ),
        ));
        $calendarId = 'primary';
        return $this->service->events->insert($calendarId, $event);
    }
    public function deteleEvent(User $seller, Event $event) {
        //Compruebo que esté logueado en calendar
        $this->loggingCalendar($seller);
        return $this->service->events->delete('primary', $event->calendar_id);
    }
    public function updateEvent(User $seller, Event $event) {
        //Compruebo que esté logueado en calendar
        $this->loggingCalendar($seller);
        // First retrieve the event from the API.
        $googleEvent = $this->service->events->get('primary', $event->calendar_id);
        $summary = Lang::get('events.reason.'.$event->reason).' a '.$event->company->name;
        $googleEvent->setSummary($summary);
        $description = $event->note;
        $description .= ($event->status)? ' (Evento realizado)':' (Evento NO realizado)';
        $googleEvent->setDescription($description);
        //Colores: ID 10 es verde. ID 5 es amarillo.
        //TODO: Agregar el IdColor en la tabla de eventos.
        $color = ($event->status)? '10': '5';
        $googleEvent->setColorId($color);
        if($event->allday) {
            $start = array(
                'date' => (new Carbon($event->date))->format('Y-m-d'),
                'timeZone' => Config::get('app.timezone'),
            );
            $end = array(
                'date' => (new Carbon($event->date))->format('Y-m-d'),
                'timeZone' => Config::get('app.timezone'),
            );
            Log::getMonolog()->info('END '.$end['date']);
            Log::getMonolog()->info('START '.$start['date']);
            $startDate = new \Google_Service_Calendar_EventDateTime();
            $startDate->setDate($start['date']);
            $startDate->setTimeZone($start['timeZone']);
            $endDate = new \Google_Service_Calendar_EventDateTime();
            $endDate->setDate($end['date']);
            $endDate->setTimeZone($end['timeZone']);
        } else {
            Log::getMonolog()->info('NO ES ALL DAY');
            $start = array(
                'dateTime' => (new Carbon($event->date))->toRfc3339String(),
                'timeZone' => Config::get('app.timezone'),
            );
            $end = array(
                'dateTime' => (new Carbon($event->date))->addHours(1)->toRfc3339String(),
                'timeZone' => Config::get('app.timezone'),
            );
            $startDate = new \Google_Service_Calendar_EventDateTime();
            $startDate->setDateTime($start['dateTime']);
            $startDate->setTimeZone($start['timeZone']);
            $endDate = new \Google_Service_Calendar_EventDateTime();
            $endDate->setDateTime($end['dateTime']);
            $endDate->setTimeZone($end['timeZone']);
        }
        $googleEvent->setStart($startDate);
        $googleEvent->setEnd($endDate);
        Log::getMonolog()->info('END ', (array) $endDate);
        Log::getMonolog()->info('',(array)$googleEvent->getStart());
        Log::getMonolog()->info('START ', (array) $startDate);
        return $this->service->events->update('primary', $event->calendar_id, $googleEvent);
    }
    public function authenticate($code, User $seller) {
        $this->client->authenticate($code);
        return $this->getAccessToken($seller);
    }
    private function setAccessToken($access_token) {
        return $this->client->setAccessToken($access_token);
    }
    private function refreshToken($seller) {
        $calendar_token = json_decode($seller->calendar_token);
        $this->client->refreshToken($seller->calendar_refresh_token);
        return $this->getAccessToken($seller);
    }
    private function getAccessToken(User $seller) {
        $accessToken = $this->client->getAccessToken();
        if(!is_null($accessToken)) {
            $seller->calendar_token = $accessToken;
            $accessToken = json_decode($accessToken);
            if(isset($accessToken->refresh_token)) {
                $seller->calendar_refresh_token = $accessToken->refresh_token;
            }
            $saved = $seller->save();
        }
        return $saved;
    }
    private function loggingCalendar(User $seller) {
        $token = json_decode($seller->calendar_token);
        $tokenCreate = Carbon::createFromTimestamp($token->created);
        $tokenExpire = $token->expires_in;
        if(Carbon::now()->diffInSeconds($tokenCreate) > $tokenExpire) {
            $this->refreshToken($seller);
        } else {
            $this->setAccessToken($seller->calendar_token);
        }
    }
    public function getColors() {
        $seller = User::whereNotNull('calendar_token')->first();
        //Para obtener los colores es necesario estar logueado.
        //Utilizo cualquier vendedor que ya se halla autentificado con calendar.
        $this->loggingCalendar($seller);
        $colors = $this->service->colors->get();
        return $colors->getEvent();
    }
}
