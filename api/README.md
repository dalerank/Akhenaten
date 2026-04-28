# Bug-report worker — deployment guide

This folder ships a single-file Cloudflare Worker that powers the
"Report a bug" page at `docs/reportbug.html`. It receives a JSON POST
from the page and opens an issue on `dalerank/Akhenaten` via the GitHub
REST API.

The page already builds and previews bug reports in your browser. To
actually post them as GitHub issues, the Worker must be deployed once
and the page wired to its URL. The whole process takes ~10 minutes and
fits comfortably in Cloudflare's free tier (100k requests/day).

---

## What's included

| File | Purpose |
| --- | --- |
| `api/report-bug.js` | The Worker. Validates input, runs spam checks, calls GitHub. |
| `wrangler.toml` (repo root) | Worker name, entry file, and non-secret env vars. |
| `package.json` (repo root) | Pins `wrangler` as a dev dependency and provides `npm run …` shortcuts. |
| `docs/reportbug.html` | The form. Has an `ENDPOINT` constant near the top of its `<script>` that you point at the deployed Worker. |

## Spam protection

Two lightweight, server-side checks — no third-party captcha:

1. **Honeypot**: a hidden `website` input. Real users never see or fill
   it; bots autofill every field. Any non-empty value → reject.
2. **Form age**: the page records `Date.now()` on load and sends it
   with the submission. The Worker rejects anything that arrives less
   than 3 seconds or more than 24 hours after page load.

If real spam ever appears, see [Adding Turnstile later](#adding-turnstile-later)
at the bottom of this file.

---

## Prerequisites

- A Cloudflare account — free tier is fine. Sign up at
  https://dash.cloudflare.com/sign-up if needed.
- Node.js (LTS) — https://nodejs.org/. Provides `npm` / `npx`.
- A GitHub fine-grained personal access token with permission to file
  issues on `dalerank/Akhenaten`. See step 1 below.

> **Note on issue authorship.** The Worker authenticates to the GitHub
> API with a single token, so every issue it opens will appear authored
> by that token's owner. The reporter's name and email (when given) are
> placed in the issue body, not as the author. If `dalerank` deploys
> with their own PAT, issues author as `dalerank`; if someone else
> deploys, issues author as them. Either is fine — the body always
> identifies the real reporter.

---

## 1. Create the GitHub token

1. Open https://github.com/settings/personal-access-tokens/new.
2. **Token name**: `akhenaten-bug-form` (or whatever).
3. **Expiration**: pick a reasonable max — you'll rotate it later with
   the same `npm run secret:github` command.
4. **Repository access** → **Only select repositories** → tick
   `dalerank/Akhenaten`.
5. **Permissions** → **Repository permissions** → **Issues**: set to
   **Read and write**.
6. Click **Generate token**. Copy the `github_pat_…` string. You'll
   paste it once in step 3; GitHub never shows it again.

---

## 2. Configure the docs origin

Open `wrangler.toml` and check that `ALLOWED_ORIGIN` matches where the
docs site is actually served from. For GitHub Pages on this repo, that's:

```toml
[vars]
ALLOWED_ORIGIN = "https://dalerank.github.io"
```

If you serve the docs from a custom domain (e.g. `akhenaten.dev`), set
that instead. The Worker rejects POSTs from any other origin, so this
must exactly match the scheme + host of the deployed page (no trailing
slash, no path).

> For local browser testing against `python -m http.server 8000`, set
> this to `http://localhost:8000` temporarily.

---

## 3. Deploy the Worker

From the **repo root** (not `api/`):

```bash
npm install            # one-time: pulls wrangler into node_modules/
npm run login          # one-time: opens a browser for Cloudflare auth
npm run secret:github  # paste the PAT from step 1 when prompted
npm run deploy         # publishes the Worker
```

On success, `wrangler` prints a URL like:

```
Published akhenaten-bug-report (1.2 sec)
  https://akhenaten-bug-report.<your-subdomain>.workers.dev
```

**Copy that URL.** You'll paste it in step 4.

---

## 4. Wire the page to the Worker

Edit `docs/reportbug.html`. Near the top of the inline `<script>`,
find:

```js
// TODO: set after deploying the serverless function (see api/report-bug.js)
const ENDPOINT = '';
```

Set it to the URL from step 3:

```js
const ENDPOINT = 'https://akhenaten-bug-report.<your-subdomain>.workers.dev';
```

Commit and deploy `docs/` (push to whichever branch GitHub Pages serves).

---

## 5. Smoke-test

1. Open the live `reportbug.html` in a browser.
2. Type a title and at least 20 characters of body. Watch the preview
   render the markdown live.
3. Click **Submit report**.
4. You should see "Reported! View on GitHub →". Click the link — the
   issue should be live on `dalerank/Akhenaten` with `bug` and
   `from-website` labels and a footer crediting the reporter.

If something fails, see [Troubleshooting](#troubleshooting).

---

## Day-to-day commands

| Need to… | Run | Notes |
| --- | --- | --- |
| Iterate on the Worker locally | `npm run dev` | Serves on `http://localhost:8787`. Point `ENDPOINT` there to test. |
| Push a code change live | `npm run deploy` | After editing `api/report-bug.js`. |
| Tail live logs | `npm run tail` | Streams real-time logs from the deployed Worker. |
| Rotate the GitHub PAT | `npm run secret:github` | Paste the new token when prompted. |
| Change `ALLOWED_ORIGIN` | edit `wrangler.toml` then `npm run deploy` | |

---

## Troubleshooting

### Browser console: "blocked by CORS policy"
`ALLOWED_ORIGIN` doesn't match where the page is served from. Fix
`wrangler.toml` and `npm run deploy` again. Remember: scheme + host,
no path, no trailing slash.

### Submission returns 502 "GitHub rejected the issue"
Most often the PAT has lost `Issues: write` on `dalerank/Akhenaten` or
expired. Regenerate (step 1) and run `npm run secret:github` to update
the secret. No redeploy needed — secrets take effect immediately.

### Submission returns 400 "Spam detected"
Either:
- The honeypot was filled. Check the form's hidden `website` input
  isn't being autofilled by a password manager (it has
  `autocomplete="off"` already, so this is rare).
- The submission arrived <3 s or >24 h after page load. Refresh and
  try again.

### `npm run deploy` errors before publishing
Usually missing/invalid `wrangler.toml` or not logged in. Run
`npm run login` first if you skipped it.

### I want to see what got submitted before GitHub posted it
Run `npm run tail` in another terminal while submitting. The Worker
doesn't log payloads by default (privacy), but you can add a
`console.log(payload)` in `api/report-bug.js` temporarily and redeploy
if you need to debug.

---

## Adding Turnstile later

Honeypot + time-check stops dumb spam but is bypassable by motivated
bots. If real spam appears, swap in [Cloudflare Turnstile][turnstile]
— a free, privacy-friendly captcha alternative.

[turnstile]: https://dash.cloudflare.com/?to=/:account/turnstile

1. **Create the Turnstile site**: in the Cloudflare dashboard →
   Turnstile → **Add site**.
   - Domain: `dalerank.github.io` (and `localhost` if you want to test
     locally).
   - Widget mode: **Managed** (recommended).
   - Copy the **site key** (public) and **secret key** (private).

2. **Add the secret to the Worker**:
   ```bash
   npx wrangler secret put TURNSTILE_SECRET
   ```
   Paste the secret key.

3. **Add the widget to `docs/reportbug.html`**:
   - In `<head>`, add:
     ```html
     <script src="https://challenges.cloudflare.com/turnstile/v0/api.js" async defer></script>
     ```
   - In the form, just before `<div class="form-actions">`, add:
     ```html
     <div class="cf-turnstile" data-sitekey="YOUR_REAL_SITE_KEY"></div>
     ```
   - In the submit handler, add the token to the payload:
     ```js
     const turnstileEl = document.querySelector('[name="cf-turnstile-response"]');
     data.turnstileToken = turnstileEl ? turnstileEl.value : '';
     ```
   - And reset the widget on success/error:
     ```js
     if (window.turnstile) window.turnstile.reset();
     ```

4. **Add server-side verification to `api/report-bug.js`**: extract
   `payload.turnstileToken`, reject if empty, then POST to
   `https://challenges.cloudflare.com/turnstile/v0/siteverify` with
   `secret=env.TURNSTILE_SECRET` and `response=token`. Reject if
   `success !== true`.

5. **Deploy**: `npm run deploy`. Test the form. Done.

The git history of this branch contains the original Turnstile
implementation — `git log --all -- api/report-bug.js` will surface it
if you'd rather copy-paste the exact code than rewrite it.
