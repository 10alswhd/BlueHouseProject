

let pushTopicSubscriptionStates = ["Sports": true, "News": false]

// an array of topics that user is subscribed to
let subscribedUserTopics = pushTopicSubscriptionStates.filter {  (_, subscribed) in  subscribed }
                                                      .map { (topic, _) in topic
}

let topicsDictionary = ["Sports": ["a", "b","c"], "Weather": ["a", "b","c"]]


let subscribedBackendTopics = topicsDictionary.filter { (key, _) in subscribedUserTopics.contains(key) }
                                              .flatMap { (_, value)  in value }


