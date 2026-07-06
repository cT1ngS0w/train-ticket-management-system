# Train Ticket Management System

## Structure

```txt
root
├── src
│   ├── modules
│   │   ├── auth        # Login, registration, role permission
│   │   ├── admin       # Station management, train schedules
│   │   ├── booking     # Ticket sales, refunds, changes
│   │   ├── inventory   # Core seat‑availability engine
│   │   └── public      # Guest inquiry portal
│   ├── shared          # Database connection, common error handlers
│   └── test            # Shared test files
├── package.json
└── .env                # Keep your secrets here!
```