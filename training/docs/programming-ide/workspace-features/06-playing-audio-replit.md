# Playing audio on Replit

Learn how to use audio on Replit by watching this video or read on below.

<iframe width="560" height="315" src="https://www.youtube.com/embed/CuIV2-ivg0U" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

## System-wide audio

[System-wide audio](https://blog.replit.com/system-audio) is an opt-in feature that delivers the PulseAudio audio stream to your browser through our [VNC](https://novnc.com) client. To enable it, add the following to your `.replit` file:

```toml
audio = true
```

Then restart your repl by running `kill 1` in the shell. You will see a checkbox with headphones in the lower right corner of the VNC output window:

![look for the headphones](https://blog.replit.com/images/system-audio/system-audio.png)

Note that due to browser security restrictions, you need to manually toggle the checkbox every time you open the Repl.

### Known limitations

Known limitations of system-wide audio include:

- A 100-300 millisecond latency introduced by the browser
- Issues with Safari's browser security model
- Not supported in Spotlight or Embed modes if enabled through secrets (as opposed to through the `.replit` file)

## Audio service

Using the audio service, you can play audio in your Repl without creating a website. This service operates on a request system and allows you to control the volume, the number of times played, and the play state of your audio files.

Supported audio file formats are `.wav`, `.aiff`, and `.mp3`. JavaScript and Python libraries are currently available. Examples of the JavaScript and Python libraries can be found in the generated docs at https://audio-js-docs--allawesome497.repl.co/ and https://replit-docs-python.allawesome497.repl.co/, respectively.

For those who prefer Rust, a community-contributed library is available [here](https://github.com/Daniel-Liu-c0deb0t/replit_audio).

## How to Develop an Audio Library

If you are new to Python or JavaScript, follow our steps below to make a library.

### Step 1: Add an audio source

Files are played in mono/single channel mode. Files with multiple channels will be read and converted into single-channel data.

Audio files are played via a request system to make this as light as possible on your repl's resources. To make a request, write to a named pipe, `/tmp/audio`.

An example request might look like this:

```json
{
  "Paused": false,
  "Name": "My tone",
  "Type": "tone",
  "Volume": 1,
  "DoesLoop": false,
  "LoopCount": 0,
  "Args": {
    "Pitch": 400,
    "Seconds": 5,
    "Type": 1,
    "Path": "  "
  }
}
```

To break it down:

- `Paused` indicates if the source is paused or not. This can only be set when updating the source.
- `Name` is the name of the source. This can be used to identify the source when it's being created. If it's not set, the name will be set by pid1.
- `Type` indicates the source type. Currently, supported types are:
  - `wav` – A `.wav` file
  - `aiff` – A `.aiff` file
  - `mp3` – A `.mp3` file
  - `tone` – A generated tone
- `Volume` is the volume of the source as a floating point number; `1` would be 100%.
- `DoesLoop` indicates if the source should loop. If true, `LoopCount` should be set.
- `LoopCount` indicates how many times the source should loop. If set to `3`, the source will restart `3` times when it is done playing the first time. If set to a negative value, it will loop forever. If `DoesLoop` is false, this value will be ignored.
- `Args` indicate additional arguments that are not used by every source type. + `Path` (used by `aiff`, `wav`, and `mp3` types) is the path to the file. This can be relative or absolute (relative to the workspace's root). + `Pitch` (used for the `tone` type) is the frequency/pitch of the tone. + `Type` (used for the `tone` type) is the wave type of the generated tone. Valid values are:
  - `0` – The sine wave type
  - `1` – The triangle wave type
  - `2` – The saw wave type
  - `3` – The sqr wave type

### Step 2: Get the status of playing audio

An example status for audio is shown below:

```json
{
  "Sources": [
    {
      "Name": "1",
      "Type": "tone",
      "Volume": 1,
      "Duration": 2000,
      "Remaining": 1995,
      "Paused": false,
      "Loop": 0,
      "ID": 1,
      "EndTime": "2020-08-20T18:15:27.763933471Z",
      "StartTime": "2020-08-20T18:15:25.763933471Z",
      "Request": {
        "ID": 0,
        "Paused": false,
        "Name": "1",
        "Type": "tone",
        "Volume": 1,
        "DoesLoop": false,
        "LoopCount": 1,
        "Args": {
          "Pitch": 400,
          "Seconds": 2,
          "Type": 1
        }
      }
    }
  ],
  "Disabled": false,
  "Running": true
}
```

In detail, this is:

- `Sources` – A list of playing sources.
  - `Name` – The name of the source.
  - `Type` – The type of the source.
  - `Volume` – The volume of the source (`float64`).
  - `Duration` – The (estimated) duration of the source (in milliseconds) (`int64`).
  - `Remaining` – The (estimated) time remaining for the source (in milliseconds) (`int64`).
  - `Paused` – Whether the source is paused or not (`bool`).
  - `Loop` – How many times the source will play itself again. Negative values are infinite (`int64`).
  - `ID` – The ID of the source used for updating it (`int64`).
  - `EndTime` – The estimated time when the source will be done playing.
  - `StartTime` – When the source started playing.
  - `Request` – The request used to create the source.
- `Disabled` – Whether the pid1 audio player is disabled. This is useful for debugging.
- `Running` – Whether pid1 is sending audio or not. This is useful for debugging.

**Notes:**
The estimated end time is based on the current loop and does not factor in the fact that the source may repeat itself.
Timestamps are formatted as: `yyyy-MM-dd'T'HH:mm:ssZ`.

To read the data from the sources, you need to read `/tmp/audioStatus.json`.
The file is formatted as shown below:

**Note:** After a source finishes playing, it is removed from the known sources.

### Step 3: Managing current sources

To pause or edit a playing source, you first need its ID.
You can get its ID by reading `/tmp/audioStatus.json`, as detailed above.

Edit requests are formatted as shown below:

```js
{
  "ID": 1, // The id of the source.
  "Volume": 1, // The volume for the source to be played at.
  "Paused": false, // Whether the file is paused or not.
  "DoesLoop": false, // Whether the file should be repeated or not.
  "LoopCount": -1 // How many times to repeat the file. Set to a negative value to create an endless loop.
}
```

All fields **must** be provided, except for `LoopCount` when `DoesLoop` is `false`.

For editing a source, you could do the following (or the equivalent in other languages):

```py
import json

class NoSuchPlayerException(Exception): pass

def update_source(id, \*\*changes):
  player_data = read_status() # Assume read_status reads /tmp/audioStatus.json

  for s in player_data['Sources']:
    if s['ID'] == id:
      data = s
      break

  if not data:
    raise NoSuchPlayerException(f'No player with id "{id}" found!')

  data.update({key.title(): changes[key] for key in changes})

  with open('/tmp/audio', 'w') as f:
    f.write(json.dumps(data))

```

There is also a simple demo created in Python available [here](https://replit.com/@AllAwesome497/Audio-Demo)
