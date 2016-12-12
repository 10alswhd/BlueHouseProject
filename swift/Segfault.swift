struct Participant {
    let identifiers: [(label: String?, value: String)]
}

// This segfaults. Combining the two maps or changing "" to nil works.
let participants = ["a", "b", "c"]
    .map { ("", $0) }
    .map { Participant(identifiers: [$0]) }

// Update: Here's an error from a later build of Swift which explains the error.
<REPL Input>:1:85: error: cannot express tuple conversion '(String, String)' to '(label: String?, value: String)' (aka '(label: Optional<String>, value: String)')
